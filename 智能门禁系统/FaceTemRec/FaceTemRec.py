#!/usr/bin/python
#coding:utf-8
"""
人脸识别和体温检测函数
"""
import os
import cv2
import serial
import time
import serial.tools.list_ports
from thermometry import thermometry
from faceAPI import *
from Threading import ThreadReturn
# from picamera import PiCamera
from Requests import postData
from faceDetectionAPI import faceDetection
from getMac import get_mac_address

mac = get_mac_address()
# mac = 'dc:a6:32:01:4f:1d'
deviceNum = '1000001'


# 获取串口
# plist = list(serial.tools.list_ports.comports())
# if len(plist) <= 0:
#     # qt界面输出红外设备未连接弹框
#     #   getFaceImg("image/read.gif")
#     print("The Serial port can't find!")
# else:
#     plist_0 = list(plist[0])
#     serialName = plist_0[0]
#     s = serial.Serial(serialName, 9600, timeout=60)
# s = serial.Serial("COM5", 9600, timeout=60)


def faceTemRec():
    # print('faceTemRec')
    # if position(cap):
    # 找不到人脸
    failDict = {'studentId': '0'}
    # 网络出现问题
    failNetDict = {'studentId': '-1'}
    try:
        # print('人脸识别体温检测')
        userList = ThreadReturn(faceRecognition())
        tem = ThreadReturn(thermometry())
        userList.start()
        tem.start()
        userList.join()
        tem.join()
        users = userList.get_result()
        Tem = tem.get_result()
        # print((users[0]))
        if int(users[0]) < 0:
            return failNetDict
        elif int(users[0]) == 0:
            # print('0')
            return failDict
        else:
            stuNum = users[0]  # 学号
            phoneNum = users[1]  # 电话号码
            score = users[2]  # 人脸匹配度
            # userTem = float(Tem)  #用户体温
            # print(type(score), score)
            # print(stuNum, phoneNum, Tem, deviceNum, mac, score)
            if float(score) > 80:
                postDict = postData(stuNum, phoneNum, Tem, deviceNum, mac)
                # print(postDict)
                return postDict
            else:
                return failDict
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("FaceTemRec.py function ERROR >>faceTemRec:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return failDict


if __name__ == '__main__':
    #     s = 1
    # while True:
    post = faceTemRec()
    print(post)
        # print(post['temperature'],post['healthCode'])
        # print(post)