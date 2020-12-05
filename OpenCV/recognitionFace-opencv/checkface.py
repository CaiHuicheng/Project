import cv2
import os


def live_detect():
    face_xml_location = os.path.join('.', 'haarcascade_frontalface_default.xml')

    # 声明cascadeclassifie对象face_cascade，用于检测人脸
    face_cascade = cv2.CascadeClassifier(face_xml_location)
    # 打开设置摄像头对象，摄像头编号默认为0
    camera = cv2.VideoCapture(0)
    # 循环检测人脸并在人脸周围绘制矩形
    while (True):
        ret, frame = camera.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = face_cascade.detectMultiScale(gray, 1.3, 5)
        for (x, y, w, h) in faces:
            img = cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 0)
        # 实时显示识别结果，按q，跳出while循环，停止识别
        cv2.imshow("camera", frame)
        if cv2.waitKey(50) & 0xff == ord("q"):
            break

    # 释放摄像头，关闭窗口
    camera.release()
    cv2.destroyAllWindows()


# 调用人脸检测函数
live_detect()
