#!/usr/bin/python
#coding:utf-8
'''
MainThread : UI界面线程
SunThread1 : 人脸识别测温线程
clearFileThread : 清除错误记录线程

人脸识别错误标识：0 人脸库中无此人脸
              -1 网络环境异常
'''
import time
import os
import sys
import pygame
import cv2

from mainWindow import *
from PyQt5.QtCore import *
from FaceTemRec import faceTemRec
from faceDetectionAPI import faceDetection
from checkNetwork import isConnected
from checkCap import checkCap
from playRecording import PlayRecording
from timeDeleteFile import ClearFile
from checkSerial import checkSerial

# s = 1


class MainThread(QThread):
    # 定义信号,定义参数为str类型
    breakSignal = pyqtSignal(str)

    def __init__(self, parent=None):
        super().__init__(parent)
        # 下面的初始化方法都可以，有的python版本不支持
        super(MainThread, self).__init__()

    def run(self):
        pass


class SunThread1(QThread):
    # 定义信号,定义参数为str类型
    breakSignal2 = pyqtSignal(dict, str, str)

    def __init__(self, parent=None):
        super().__init__(parent)
        # 下面的初始化方法都可以，有的python版本不支持
        super(SunThread1, self).__init__()

    def run(self):
        checkImage = os.getcwd() + "//faceImage.jpg"
        # print(checkImage)
        while True:
            try:
                # 初始化界面
                time_start = time.time()
                data = {'studentId': '---', 'college': '---', 'studentName': '---', 'temperature': '---',
                        'className': '---', 'healthCode': '---'}
                path = os.getcwd()+"/image/tishi.jpg"  # 初始界面，显示提示信息
                pathState = "image/FaceFrame.png"
                self.breakSignal2.emit(data, path, pathState)
                time.sleep(0.01)
                # 每次人脸检测时，检测测试设备
                # if s == 0:
                if checkSerial():
                    # print('test')
                    pathSerialFail = os.getcwd()+"/image/state05.png"
                    self.breakSignal2.emit(data, path, pathSerialFail)
                    time.sleep(1)
                elif isConnected():
                    pathNetWorkFail = os.getcwd()+"/image/state06.png"
                    self.breakSignal2.emit(data, path, pathNetWorkFail)
                    time.sleep(1)
                # 废除该视频流，移交到mianWindow.py showVideo检测
                # elif checkCap():
                #     pathCapFail = "image/state05.png"
                #     self.breakSignal.emit(pathCapFail)
                #     time.sleep(1)
                elif os.path.isfile(checkImage):
                    checkFace = faceDetection()
                    # checkFace = 1
                    # print(checkFace)
                    if checkFace > 0:
                        # 检测到人脸，进行人脸识别和体温检测
                        # print('checkData')
                        pathLoad = os.getcwd()+"/image/load.jpg"
                        pathStateLoad = os.getcwd()+"/image/FaceRecState.png"
                        self.breakSignal2.emit(data, pathLoad, pathStateLoad)
                        data = faceTemRec()
                        try:
                            checkData = int(data['studentId'])
                            # print('check:%s',checkData)
                        except Exception:
                            checkData = 0
#                         time.sleep(2)
#                         checkData = 1
#                         data = {'studentId': '111', 'college': '111', 'studentName': '111', 'temperature': '111',
#                                 'className': '111', 'healthCode': '111'}
                        time_load = time.time()
                        print('loadTime:',time_load - time_start)
                        if checkData > 0:
                        # 检测到人脸在人脸库中，返回数据，显示个人信息
                            dataSuccess = data
                            pathFace = os.getcwd()+"/userFace.jpg"
                            # print(data)
                            # 体温小于37.2且健康码为绿色 通行
                            if float(dataSuccess['temperature']) <= 37.2 and dataSuccess['healthCode'] == '绿色':
                                pathStateSuccess = os.getcwd()+"/image/state01.png"
                                self.breakSignal2.emit(dataSuccess, pathFace, pathStateSuccess)
                                # playMusic("music/success.mp3")
                                # time.sleep(0.1)
                                # time.sleep(2)
                                PlayRecording(os.getcwd()+"/music/success.mp3")
                                pygame.mixer.music.play()
                                time.sleep(2)
                                pygame.mixer.music.stop()
                            # 体温小于37.2且健康码为黄色 不通行
                            elif float(dataSuccess['temperature']) <= 37.2 and dataSuccess['healthCode'] == '黄色':
                                pathStateSuccess = os.getcwd()+"/image/state01.png"
                                self.breakSignal2.emit(dataSuccess, pathFace, pathStateSuccess)
                                PlayRecording(os.getcwd()+"/music/healthOrange.mp3")
                                pygame.mixer.music.play()
                                time.sleep(1)
                                pygame.mixer.music.stop()
                            # 体温小于37.2且健康码为红色 不通行
                            elif float(dataSuccess['temperature']) <= 37.2 and dataSuccess['healthCode'] == '红色':
                                pathStateSuccess = os.getcwd()+"/image/state01.png"
                                self.breakSignal2.emit(dataSuccess, pathFace, pathStateSuccess)
                                PlayRecording(os.getcwd()+"/music/healthRed.mp3")
                                pygame.mixer.music.play()
                                time.sleep(1)
                                pygame.mixer.music.stop()
                            else:
                                pathStateFail = os.getcwd()+"/image/state03.png"
                                self.breakSignal2.emit(data, pathFace, pathStateFail)
                                # playMusic("music/abnTemperature.mp3")
                                # time.sleep(0.1)
                                PlayRecording(os.getcwd()+"/music/abnTemperature.mp3")
                                pygame.mixer.music.play()
                                time.sleep(2)
                                pygame.mixer.music.stop()
                                # time.sleep(2)
                        elif checkData == -1:
                            # print('data')
                            pathLoad = os.getcwd()+"/image/load.jpg"
                            pathNetWorkFail = os.getcwd()+"/image/state06.png"
                            self.breakSignal2.emit(data, pathLoad, pathNetWorkFail)
                            PlayRecording(os.getcwd()+"/music/networkAbnormal.mp3")
                            pygame.mixer.music.play()
                            time.sleep(1)
                            pygame.mixer.music.stop()
                        elif checkData == 0:
                            data = {'studentId': '---', 'college': '---', 'studentName': '---', 'temperature': '---',
                                    'className': '---', 'healthCode': '---'}
                            # 未检测到人脸
                            pathStateCheckFail = os.getcwd()+"/image/state02.png"
                            path = os.getcwd()+"/image/load.jpg"
                            self.breakSignal2.emit(data, path, pathStateCheckFail)
                            # time.sleep(2)
                            # playMusic("music/faceRecFail.mp3")
                            # time.sleep(0.1)
                            PlayRecording(os.getcwd()+"/music/faceRecFail.mp3")
                            pygame.mixer.music.play()
                            time.sleep(1)
                            pygame.mixer.music.stop()
                    elif checkFace == -1:
                        data = {'studentId': '---', 'college': '---', 'studentName': '---', 'temperature': '---',
                                'className': '---', 'healthCode': '---'}
                        pathLoad = os.getcwd()+"/image/load.jpg"
                        pathNetWorkFail = os.getcwd()+"/image/state06.png"
                        self.breakSignal2.emit(data, pathLoad, pathNetWorkFail)
                        PlayRecording(os.getcwd()+"/music/networkAbnormal.mp3")
                        pygame.mixer.music.play()
                        time.sleep(1)
                        pygame.mixer.music.stop()
                    else:
                        continue
                else:
                    continue
                time_end = time.time()
                print('allTime:',time_end - time_start)
            except Exception as e:
                curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
                f = open(os.getcwd()+'/Log.txt', 'a')
                f.write("main.py Function Error >>QThread2 run:" + str(e) + "     " + "Time:" + str(
                    curren_time) + '\n')
                f.close()


class clearFileThread(QThread):
    # 定义信号,定义参数为str类型
    breakSignal = pyqtSignal()

    def __init__(self, parent=None):
        super().__init__(parent)
        # 下面的初始化方法都可以，有的python版本不支持
        super(clearFileThread, self).__init__()
        self.time_left = 24*60*60

    def run(self):
        while True:
            try:
                time.sleep(1)
                self.time_left = self.time_left - 1
                # print(self.time_left)
                if self.time_left <= 0:
                    ClearFile()
                    self.time_left = 24*60*60
            except Exception as e:
                curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
                f = open(os.getcwd()+'/Log.txt', 'a')
                f.write("main.py Function Error >>QThread3 run:" + str(e) + "     " + "Time:" + str(
                    curren_time) + '\n')
                f.close()





class MainWindow(QWidget):

    def __init__(self):
        # call QWidget constructor
        super().__init__()
        self.ui = Ui_Form()
        self.ui.setupUi(self)

        # 按钮启动现成
        # self.ui.control_bt.clicked.connect(self.controlTimer)

        # 创建线程
        self.thread = MainThread()
        # 连接信号
        self.thread.breakSignal.connect(self.checkTool)
        self.thread.start()
        # 开始线程

        # 创建线程
        self.thread2 = SunThread1()
        self.thread2.breakSignal2.connect(self.changeData)
        self.thread2.start()

        self.thread3 = clearFileThread()
        self.thread3.start()


    # 修改UI界面数据
    def changeData(self, msg, path, pathState):
        self.ui.updateShowInfo(msg)
        self.ui.updateShowImg(path)
        self.ui.getFaceImg(pathState)

    def checkTool(self, path):
        self.ui.getFaceImg(path)

    def controlTimer(self):
        self.thread.start()


if __name__ == '__main__':
    # time.sleep(10)
    app = QApplication(sys.argv)
    # create and show mainWindow
    mainWindow = MainWindow()
    mainWindow.setWindowTitle("人脸识别测温系统")
    mainWindow.show()
    sys.exit(app.exec_())
