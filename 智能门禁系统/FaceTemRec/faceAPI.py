#!/usr/bin/python
#coding:utf-8
"""
调用百度API进行人脸识别
"""
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
client.setSocketTimeoutInMillis(5000)  # 通过打开的连接传输数据的超时时间（单位：毫秒）
# 图像编码方式
IMAGE_TYPE = 'BASE64'
# camera = PiCamera()
# 用户组
GROUP = 'student'
global null
null = ''
imagePath = os.getcwd() + "/faceImage.jpg"
imagePath2 = os.getcwd() + "/userFace.jpg"


# # 照相函数
# def getimage():
#     try:
#         # cap.set(4, 480)
#         # time.sleep(0.1)
#         # ret, frame = cap.read()
#         # cv2.imshow("capture", frame)
#         # cv2.waitKey(1)
#         # camera.capture('faceimage.jpg')
#         frame = cv2.imread('faceImage.jpg')
#         cv2.imwrite('faceimage.jpg', frame)  # 拍照并保存
#     except Exception as e:
#         print("faceAPI.py function Error >>getimage：", e)


# 对图片的格式进行转换
def transimage():
    try:
        f = open(imagePath2, 'rb')
        img = base64.b64encode(f.read())
        return img
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("faceAPI.py function Error >> trensimage:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return 0


# 上传到百度api进行人脸检测
def go_api(image):
    try:
        try:
            result = client.search(str(image, 'utf-8'), IMAGE_TYPE, GROUP);  # 在百度云人脸库中寻找有没有匹配的人脸
        except Exception as e:
            return ['-1','0','0']
        # print(result)
        if result['error_msg'] == 'SUCCESS':  # 如果成功了
            user_info = result['result']['user_list'][0]['user_info']  # 获取名字
            score = result['result']['user_list'][0]['score']  # 获取相似度
            # if score > 80:  # 如果相似度大于90
            #     print("欢迎%s !" % name)
            #     time.sleep(0.1)
            # else:
            #     print("对不起，我不认识你！")
            #     name = 'Unknow'
            #     return 0
            try:
                userlist = user_info.split('-')
                phoneNum = userlist[0]
                stuNum = userlist[1]
            # print("欢迎%s !" % stuNum)
                user = [stuNum, phoneNum, score]
                return user
            except Exception as e:
                return ['0','0','0']
            # curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间

            # 将人员出入的记录保存到Log.txt中
            # f = open('Log.txt', 'a')
            # f.write("Person: " + user_info + "     " + "Time:" + str(curren_time) + '\n')
            # f.close()
        else:
            return ['0','0','0']
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("faceAPI.py function Error >>go_api:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return ['0','0','0']


def faceRecognition():
    # camera.resolution = (600,500)#摄像界面为1024*768
    # camera.start_preview()#开始摄像
    # cap.set(3, 500)
    # cap.set(4, 480)
    # print('faceAPI')
    try:
        if True:
            # getimage()  # 拍照
            img = transimage()  # 转换照片格式
            if img != 0:
                res = go_api(img)  
            else:
                return ['0','0','0']
        return res
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("faceAPI.py function Error >>faceRecognition:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return ['0','0','0']


# 主函数
if __name__ == '__main__':
    while True:
        time_start = time.time()
        res = faceRecognition()
        print(res)
        # camera.stop_preview()#结束摄像
        time_end = time.time()
        print(time_end - time_start)
