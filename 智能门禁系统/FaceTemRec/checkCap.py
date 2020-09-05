#!/usr/bin/python
#coding:utf-8
"""
checkCap:检测摄像头是否链接正常
"""
import time
import os

import cv2


def checkCap():
    # print('checkC')	
    try:
        ret, frame = cap.read()
        if ret:
            return False
        else:
            return True
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("checkNetwork.py Function Error>>checkCap:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return True


if __name__ == '__main__':
    cap = cv2.VideoCapture(0)
    while True:
        ret = checkCap()
        print(ret)
