#!/usr/bin/python
#coding:utf-8
from thermometry import thermometry
from faceAPI import *
from threading import Thread
import time
# from picamera import PiCamera
from Requests import postData

"""重新定义带返回值的线程类"""


class ThreadReturn(Thread):
    def __init__(self, func):
        super(ThreadReturn, self).__init__()
        self.func = func

    def run(self):
        self.result = self.func

    def get_result(self):
        try:
            return self.result
        except Exception:
            return None


# threads = []
# threads.addend(threading.Thread(target = faceRecognition()))
# threads.addend(threading.Thread(target = thermometry()))


if __name__ == '__main__':
    mac = 'dc:a6:32:01:4f:1d'
    deviceNum = '1000001'
    time_start = time.time()
    userList = ThreadReturn(faceRecognition())
    tem = ThreadReturn(thermometry())
    userList.start()
    tem.start()
    userList.join()
    tem.join()
    users = userList.get_result()
    Tem = tem.get_result()
    # print(type(users[0]))
    if int(users[0]) < 0:
        print('1')
    elif int(users[0]) == 0:
        print('0')
    else:
        stuNum = users[0]  # 学号
        phoneNum = users[1]  # 电话号码
        score = users[2]  # 人脸匹配度
        # userTem = float(Tem)  #用户体温
        # print(type(score), score)
        # print(stuNum, phoneNum, Tem, deviceNum, mac, score)
        if float(score) > 80:
            postDict = postData(stuNum, phoneNum, Tem, deviceNum, mac)
            print(stuNum)
    time_end = time.time()
    print(time_end - time_start)
    # camera.stop_preview()#结束摄像
    exit()
