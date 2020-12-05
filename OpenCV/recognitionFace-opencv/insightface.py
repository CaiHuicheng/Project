import os
import yaml
import numpy as np
import insightface
import cv2
from utils import log_util
from utils.utils import get_user_id
from sklearn import preprocessing


@staticmethod
def feature_compare(feature1, feature2, threshold):
    diff = np.subtract(feature1, feature2)
    dist = np.sum(np.square(diff), 1)
    log_util.logger.info("人脸欧氏距离：%f" % dist)
    if dist < threshold:
        return True
    else:
        return False


# Deploy Configuration File Parser
class DeployConfig:
    def __init__(self, conf_file):
        if not os.path.exists(conf_file):
            raise Exception('Config file path [%s] invalid!' % conf_file)

        with open(conf_file) as fp:
            configs = yaml.load(fp, Loader=yaml.FullLoader)
            deploy_conf = configs["FACE"]
            # 正数为GPU的ID，负数为使用CPU
            self.gpu_id = deploy_conf["GPU_ID"]
            self.face_db = deploy_conf["FACE_DB"]
            self.threshold = deploy_conf["THRESHOLD"]
            self.nms = deploy_conf["NMS"]


class FaceRecognition:
    def __init__(self, conf_file):
        self.config = DeployConfig(conf_file)
        # 加载人脸识别模型
        self.model = insightface.app.FaceAnalysis()
        self.model.prepare(ctx_id=self.config.gpu_id, nms=self.config.nms)
        # 人脸库的人脸特征
        self.faces_embedding = list()
        # 加载人脸库中的人脸
        self.load_faces(self.config.face_db)

    # 加载人脸库中的人脸
    def load_faces(self, face_db_path):
        if not os.path.exists(face_db_path):
            os.makedirs(face_db_path)
        for root, dirs, files in os.walk(face_db_path):
            for file in files:
                input_image = cv2.imdecode(np.fromfile(os.path.join(root, file), dtype=np.uint8), 1)
                user_id = file.split(".")[0]
                log_util.logger.info("加载人脸：%s" % user_id)
                face = self.model.get(input_image)[0]
                embedding = np.array(face.embedding).reshape((1, -1))
                embedding = preprocessing.normalize(embedding)
                self.faces_embedding.append({
                    "user_id": user_id,
                    "feature": embedding
                })

    def recognition(self, image):
        faces = self.model.get(image)
        results = list()
        for face in faces:
            result = dict()
            # 获取人脸属性
            result["bbox"] = np.array(face.bbox).astype(np.int32).tolist()
            result["landmark"] = np.array(face.landmark).astype(np.int32).tolist()
            result["age"] = face.age
            gender = '男'
            if face.gender == 0:
                gender = '女'
            result["gender"] = gender
            # 开始人脸识别
            embedding = np.array(face.embedding).reshape((1, -1))
            embedding = preprocessing.normalize(embedding)
            result["user_id"] = "unknown"
            for com_face in self.faces_embedding:
                log_util.logger.info("和%s进行对比" % com_face["user_id"])
                r = self.feature_compare(embedding, com_face["feature"], self.config.threshold)
                if r:
                    result["user_id"] = com_face["user_id"]
            results.append(result)
        return results

    def register(self, image):
        faces = self.model.get(image)
        if len(faces) != 1:
            log_util.logger.info("没有检测到人脸，无法注册")
            return None
        # 判断人脸是否存在
        embedding = np.array(faces[0].embedding).reshape((1, -1))
        embedding = preprocessing.normalize(embedding)
        is_exits = False
        for com_face in self.faces_embedding:
            r = self.feature_compare(embedding, com_face["feature"], self.config.threshold)
            if r:
                is_exits = True
        if is_exits:
            log_util.logger.info("人脸已存在，无法注册")
            return None
        old_user_id = [d["user_id"] for d in self.faces_embedding]
        user_id = get_user_id(old_user_id)
        # 符合注册条件保存图片，同时把特征添加到人脸特征库中
        cv2.imencode('.png', image)[1].tofile(os.path.join(self.config.face_db, '%s.png' % user_id))
        self.faces_embedding.append({
            "user_id": user_id,
            "feature": embedding
        })
        return user_id


if __name__ == '__main__':
    img = cv2.imread("1711610035.jpg")
    face_recognitio = FaceRecognition("config.yml")
    user_id = face_recognitio.register(img)
    print(user_id)

    img = cv2.imread("test.jpg")
    result = face_recognitio.recognition(img)
    print(result)

