#!/usr/bin/python
#coding:utf-8
import ast
import os
import urllib
from urllib.parse import urlencode

from aip import AipFace
# from picamera import PiCamera
import cv2
import base64
import time

# 百度人脸识别API账号信息
APP_ID = '19648175'  # APP_ID
API_KEY = '4zdAiGS6aW38C8QaL1uvXiBc'  # API_KEY
SECRET_KEY = '0bpQiqNCKygcGu0bG7ECwZxcWvuXRUsI'  # SECRET_KEY
client = AipFace(APP_ID, API_KEY, SECRET_KEY)  # 创建一个客户端用以访问百度云
client.setConnectionTimeoutInMillis(1000)  # 建立连接的超时时间（单位：毫秒）
client.setSocketTimeoutInMillis(4000)  # 通过打开的连接传输数据的超时时间（单位：毫秒）
# 图像编码方式
IMAGE_TYPE = 'BASE64'
# camera = PiCamera()
# 用户组
GROUP = 'student'
global null
null = ''
imagePath = os.getcwd() + "/faceImage.jpg"
imagePath2 = os.getcwd() + "/userFace.jpg"
"""
调用百度API进行人脸检测
"""

# 照相函数
def getimage():
    try:
        # cap.set(4, 480)
        # time.sleep(0.1)
        # ret, frame = cap.read()
        # cv2.imshow("capture", frame)
        # cv2.waitKey(1)
        # camera.capture('faceimage.jpg')
        faceFrame = cv2.imread(imagePath)
        cv2.imwrite(imagePath2, faceFrame)  # 保存人脸检测到的人脸信息
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("faceDetectionAPI.py function Error >>getimage：" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()


# 对图片的格式进行转换
def transimage():
    try:
        f = open(imagePath2, 'rb')
        img = base64.b64encode(f.read())
        return img
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("faceDetectionAPI.py function Error >> trensimage:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()


# 上传到百度api进行人脸检测
def go_api(image):
    try:
        # face = cv2.imread(imagePath2)
        # # 请求地址
        # request_url = "https://aip.baidubce.com/rest/2.0/face/v3/detect"
        # # 请求参数
        # params = {'image': '' + str(image, 'utf-8') + '', 'image_type': 'BASE64'}
        # # 对base64数据进行urlencode处理
        # params = urlencode(params)
        # # 生成的access_token
        # access_token = '24.751bf35911ecbaad868595750dbafc60.2592000.1591143488.282335-19689234'
        # request_url = request_url + "?access_token=" + access_token
        # request = urllib.request.Request(url=request_url, data=params.encode("utf-8"))
        # request.add_header('Content-Type', 'application/json')
        try:
            # 检测网络是否异常
            # response = urllib.request.urlopen(request, timeout=5)
            result = client.detect(str(image, 'utf-8'), IMAGE_TYPE)  # 在百度云人脸检测
            left = result['result']['face_list'][0]['location']['left']
            top = result['result']['face_list'][0]['location']['top']
            # width = result['result']['face_list'][0]['location']['width']
            # height = result['result']['face_list'][0]['location']['width']
            # print(left)
            # print(top)
            # print(width)
            # print(height)
            checkContent = result['error_msg']
            # print(checkContent)
        except Exception:
            return 0
        if checkContent == 'SUCCESS':
            # print('test')
            # 人脸框选部分
            # left_top = (
            #     left,
            #     top)
            # right_bottom = ((left_top[0] + width),
            #                 (left_top[1] + height))
            # cv2.rectangle(face, left_top, right_bottom, (0, 0, 255), 2)
            if 150 <= left <= 380 and 120 <= top <= 320:
                return 1
            else:
                return 0
        elif checkContent == 'pic not has face':
            print('检测不到人脸')
            # time.sleep(0.1)
            return 0
        else:
            print(checkContent + ' ' + checkContent)
            return 0
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("faceDetectionAPI.py function Error >> go_api:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return 0


def faceDetection():
    # camera.resolution = (600,500)#摄像界面为1024*768
    # camera.start_preview()#开始摄像
    # cap.set(3, 500)
    # print('faceDetection')
    try:
        if True:
            getimage()  # 拍照
            img = transimage()  # 转换照片格式
            res = go_api(img)  # 将转换了格式的图片上传到百度云
            # os.remove('faceImage.jpg')
        return res
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("faceDetectionAPI.py function Error >> faceRecognition:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return 0


# 主函数
if __name__ == '__main__':
    time_start = time.time()
    time.sleep(0.1)
    res = faceDetection()
    print(res)
    # camera.stop_preview()#结束摄像
    time_end = time.time()
    print(time_end - time_start)
