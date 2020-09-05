#!/usr/bin/python
#coding:utf-8
# Form implementation generated from reading ui file 'mainWindow.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!
import time

import cv2
import os
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtWidgets import *
from PyQt5.QtCore import QDate, QTime, QDateTime, Qt, QTimer
from faceDetectionAPI import faceDetection


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("人脸识别测温系统")
        Form.resize(498, 711)
        Form.setStyleSheet("QFrame#bottomFrame,#topFrame{\n"
                           "    background-color:#1d88fa;\n"
                           "}\n"
                           "\n"
                           "QFrame#topFrame QLabel{\n"
                           "    color:#f1ffff;\n"
                           "}\n"
                           "\n"
                           "QFrame#lbFrame QLabel{\n"
                           "    color:#f1ffff;\n"
                           "}")

        Form.setMinimumSize(QtCore.QSize(480, 700))
        Form.setMaximumSize(QtCore.QSize(480, 700))
        self.verticalLayout = QtWidgets.QVBoxLayout(Form)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.frame = QtWidgets.QFrame(Form)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame.sizePolicy().hasHeightForWidth())
        self.frame.setSizePolicy(sizePolicy)
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)

        self.verticalLayout_8 = QtWidgets.QVBoxLayout(self.frame)
        self.verticalLayout_8.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_8.setSpacing(0)
        self.verticalLayout_8.setObjectName("verticalLayout_8")
        self.topFrame = QtWidgets.QFrame(self.frame)
        self.topFrame.setMinimumSize(QtCore.QSize(0, 60))
        self.topFrame.setMaximumSize(QtCore.QSize(16777215, 60))
        self.topFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.topFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.topFrame.setObjectName("topFrame")
        self.horizontalLayout_8 = QtWidgets.QHBoxLayout(self.topFrame)
        self.horizontalLayout_8.setContentsMargins(10, 5, 10, 5)
        self.horizontalLayout_8.setSpacing(2)
        self.horizontalLayout_8.setObjectName("horizontalLayout_8")
        self.lbIcon = QtWidgets.QLabel(self.topFrame)
        self.lbIcon.setMinimumSize(QtCore.QSize(40, 40))
        self.lbIcon.setMaximumSize(QtCore.QSize(40, 40))
        self.lbIcon.setText("")
        self.lbIcon.setObjectName("lbIcon")
        self.horizontalLayout_8.addWidget(self.lbIcon)
        self.lbTitle = QtWidgets.QLabel(self.topFrame)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lbTitle.sizePolicy().hasHeightForWidth())
        self.lbTitle.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(18)
        font.setBold(True)
        font.setWeight(75)
        self.lbTitle.setFont(font)
        self.lbTitle.setObjectName("lbTitle")
        self.horizontalLayout_8.addWidget(self.lbTitle)
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.label_10 = QtWidgets.QLabel(self.topFrame)
        self.label_10.setMinimumSize(QtCore.QSize(90, 20))
        self.label_10.setMaximumSize(QtCore.QSize(90, 20))
        self.label_10.setAlignment(QtCore.Qt.AlignCenter)
        self.label_10.setObjectName("label_10")
        # 字大小
        font1 = QtGui.QFont()
        font1.setPointSize(10)
        font1.setWeight(70)
        self.label_10.setFont(font1)

        self.verticalLayout_3.addWidget(self.label_10)
        self.label_9 = QtWidgets.QLabel(self.topFrame)
        self.label_9.setMinimumSize(QtCore.QSize(90, 20))
        self.label_9.setMaximumSize(QtCore.QSize(90, 20))
        self.label_9.setAlignment(QtCore.Qt.AlignCenter)
        self.label_9.setObjectName("label_9")
        self.label_9.setFont(font1)

        self.verticalLayout_3.addWidget(self.label_9)
        self.horizontalLayout_8.addLayout(self.verticalLayout_3)
        self.label = QtWidgets.QLabel(self.topFrame)
        self.label.setMinimumSize(QtCore.QSize(90, 0))
        self.label.setMaximumSize(QtCore.QSize(90, 16777215))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(22)
        self.label.setFont(font)
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        self.horizontalLayout_8.addWidget(self.label)
        self.verticalLayout_8.addWidget(self.topFrame)
        self.label.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)

        self.verticalLayout_8.setContentsMargins(0, 0, 0, 0)
        # 显示图像
        self.lbShowMainImg = QtWidgets.QLabel(self.frame)
        self.lbShowMainImg.setText("")
        self.lbShowMainImg.setObjectName("lbShowMainImg")
        self.verticalLayout_8.addWidget(self.lbShowMainImg)
        self.verticalLayout.addWidget(self.frame)
        # 添加面部背景
        self.lbBckImg = QtWidgets.QLabel(self.lbShowMainImg)
        self.lbBckImg.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        # 设置面部背景图像
        self.lbBckImg.setPixmap(QtGui.QPixmap(os.getcwd()+"/image/FaceFrame.png"))
        self.lbBckImg.setScaledContents(True)
        # 添加面部背景
        self.mainImgVLayout = QtWidgets.QVBoxLayout()
        self.lbShowMainImg.setLayout(self.mainImgVLayout)
        self.mainImgVLayout.setContentsMargins(0, 0, 0, 0)
        self.mainImgVLayout.addWidget(self.lbBckImg)

        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.bottomFrame = QtWidgets.QFrame(Form)
        self.bottomFrame.setMinimumSize(QtCore.QSize(0, 220))
        self.bottomFrame.setMaximumSize(QtCore.QSize(16777215, 220))
        self.bottomFrame.setStyleSheet("")
        self.bottomFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.bottomFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.bottomFrame.setObjectName("bottomFrame")
        self.horizontalLayout_5 = QtWidgets.QHBoxLayout(self.bottomFrame)
        self.horizontalLayout_5.setObjectName("horizontalLayout_5")
        # 设置显示比例
        self.horizontalLayout_5.setStretch(0, 1)
        self.horizontalLayout_5.setStretch(1, 1)
        self.lbShowImg = QtWidgets.QLabel(self.bottomFrame)
        self.lbShowImg.setText("")
        self.lbShowImg.setObjectName("lbShowImg")
        self.horizontalLayout_5.addWidget(self.lbShowImg)
        self.lbFrame = QtWidgets.QFrame(self.bottomFrame)
        self.lbFrame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.lbFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.lbFrame.setObjectName("lbFrame")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.lbFrame)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.label_6 = QtWidgets.QLabel(self.lbFrame)
        self.label_6.setMinimumSize(QtCore.QSize(0, 23))
        self.label_6.setMaximumSize(QtCore.QSize(16777215, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_6.setFont(font)
        self.label_6.setAlignment(QtCore.Qt.AlignCenter)
        self.label_6.setObjectName("label_6")
        self.verticalLayout_2.addWidget(self.label_6)
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label_2 = QtWidgets.QLabel(self.lbFrame)
        self.label_2.setMinimumSize(QtCore.QSize(100, 23))
        self.label_2.setMaximumSize(QtCore.QSize(100, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_2.setFont(font)
        self.label_2.setAlignment(QtCore.Qt.AlignCenter)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_4.addWidget(self.label_2)
        self.lbID = QtWidgets.QLabel(self.lbFrame)
        self.lbID.setMinimumSize(QtCore.QSize(0, 23))
        self.lbID.setMaximumSize(QtCore.QSize(16777215, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.lbID.setFont(font)
        self.lbID.setAlignment(QtCore.Qt.AlignCenter)
        self.lbID.setObjectName("lbID")
        self.horizontalLayout_4.addWidget(self.lbID)
        self.verticalLayout_2.addLayout(self.horizontalLayout_4)
        self.horizontalLayout_6 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_6.setObjectName("horizontalLayout_6")
        self.label_7 = QtWidgets.QLabel(self.lbFrame)
        self.label_7.setMinimumSize(QtCore.QSize(100, 23))
        self.label_7.setMaximumSize(QtCore.QSize(100, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_7.setFont(font)
        self.label_7.setAlignment(QtCore.Qt.AlignCenter)
        self.label_7.setObjectName("label_7")
        self.horizontalLayout_6.addWidget(self.label_7)
        self.lbName = QtWidgets.QLabel(self.lbFrame)
        self.lbName.setMinimumSize(QtCore.QSize(0, 23))
        self.lbName.setMaximumSize(QtCore.QSize(16777215, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.lbName.setFont(font)
        self.lbName.setAlignment(QtCore.Qt.AlignCenter)
        self.lbName.setObjectName("lbName")
        self.horizontalLayout_6.addWidget(self.lbName)
        self.verticalLayout_2.addLayout(self.horizontalLayout_6)
        self.horizontalLayout_9 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_9.setObjectName("horizontalLayout_9")
        self.label_4 = QtWidgets.QLabel(self.lbFrame)
        self.label_4.setMinimumSize(QtCore.QSize(100, 23))
        self.label_4.setMaximumSize(QtCore.QSize(100, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_4.setFont(font)
        self.label_4.setAlignment(QtCore.Qt.AlignCenter)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_9.addWidget(self.label_4)
        self.lbCollege = QtWidgets.QLabel(self.lbFrame)
        self.lbCollege.setMinimumSize(QtCore.QSize(0, 23))
        self.lbCollege.setMaximumSize(QtCore.QSize(16777215, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.lbCollege.setFont(font)
        self.lbCollege.setAlignment(QtCore.Qt.AlignCenter)
        self.lbCollege.setObjectName("lbCollege")
        self.horizontalLayout_9.addWidget(self.lbCollege)
        self.verticalLayout_2.addLayout(self.horizontalLayout_9)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.lb600 = QtWidgets.QLabel(self.lbFrame)
        self.lb600.setMinimumSize(QtCore.QSize(100, 23))
        self.lb600.setMaximumSize(QtCore.QSize(100, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.lb600.setFont(font)
        self.lb600.setAlignment(QtCore.Qt.AlignCenter)
        self.lb600.setObjectName("lb600")
        self.horizontalLayout_2.addWidget(self.lb600)
        self.lbMajor = QtWidgets.QLabel(self.lbFrame)
        self.lbMajor.setMinimumSize(QtCore.QSize(0, 23))
        self.lbMajor.setMaximumSize(QtCore.QSize(16777215, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.lbMajor.setFont(font)
        self.lbMajor.setAlignment(QtCore.Qt.AlignCenter)
        self.lbMajor.setObjectName("lbMajor")
        self.horizontalLayout_2.addWidget(self.lbMajor)
        self.verticalLayout_2.addLayout(self.horizontalLayout_2)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.label_3 = QtWidgets.QLabel(self.lbFrame)
        self.label_3.setMinimumSize(QtCore.QSize(100, 23))
        self.label_3.setMaximumSize(QtCore.QSize(100, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_3.setFont(font)
        self.label_3.setAlignment(QtCore.Qt.AlignCenter)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_3.addWidget(self.label_3)
        self.lbTempera = QtWidgets.QLabel(self.lbFrame)
        self.lbTempera.setMinimumSize(QtCore.QSize(0, 23))
        self.lbTempera.setMaximumSize(QtCore.QSize(16777215, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.lbTempera.setFont(font)
        self.lbTempera.setAlignment(QtCore.Qt.AlignCenter)
        self.lbTempera.setObjectName("lbTempera")
        self.horizontalLayout_3.addWidget(self.lbTempera)
        self.verticalLayout_2.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_7 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_7.setObjectName("horizontalLayout_7")
        self.label_8 = QtWidgets.QLabel(self.lbFrame)
        self.label_8.setMinimumSize(QtCore.QSize(100, 23))
        self.label_8.setMaximumSize(QtCore.QSize(100, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label_8.setFont(font)
        self.label_8.setAlignment(QtCore.Qt.AlignCenter)
        self.label_8.setObjectName("label_8")
        self.horizontalLayout_7.addWidget(self.label_8)
        self.lbStatus = QtWidgets.QLabel(self.lbFrame)
        self.lbStatus.setMinimumSize(QtCore.QSize(0, 23))
        self.lbStatus.setMaximumSize(QtCore.QSize(16777215, 23))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.lbStatus.setFont(font)
        self.lbStatus.setAlignment(QtCore.Qt.AlignCenter)
        self.lbStatus.setObjectName("lbStatus")
        self.horizontalLayout_7.addWidget(self.lbStatus)
        self.verticalLayout_2.addLayout(self.horizontalLayout_7)
        self.horizontalLayout_5.addWidget(self.lbFrame)
        self.horizontalLayout.addWidget(self.bottomFrame)
        self.verticalLayout.addLayout(self.horizontalLayout)

        self.lbShowImg.setMinimumSize(QtCore.QSize(180, 0))
        self.lbShowImg.setMaximumSize(QtCore.QSize(180, 11111))

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)
        # 对显示摄像头视频和人脸检测频率进行划分 4:1
        self.count = 0
        # # 执行人脸识别程序控制位
        # self.flag = 0
        # 显示时间
        self.timer = QTimer()
        self.timer.timeout.connect(self.getDate)
        self.timer.start(1000)
        self.cap = cv2.VideoCapture(0)
        self.cap.set(3, 480)
        # self.cap.set(4, 480)
        self.timer_camera = QTimer()
        # 显示人脸视频流在UI界面上
        # self.cap = cv2.VideoCapture(0)
        # 1s 40帧图像
        self.timer_camera.timeout.connect(self.showVideo)
        self.timer_camera.start(25)

        # # 调用更新显示更新显示信息调用
        # data = {'studentId': '---', 'college': '---', 'studentName': '---', 'temperature': '---',
        #         'className': '---', 'healthCode': '---'}
        # self.updateShowInfo(data)
        # #
        # # # 调用更新显示图像#
        # path = "image/tishi.jpg"
        # self.updateShowImg(path)
        #
        # 更新人脸识别图像
        # self.getFaceImg("tishi.jpg")

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.lbTitle.setText(_translate("Form", "请在区域中进行识别..."))
        self.label_10.setText(_translate("Form", "TextLabel"))
        self.label_9.setText(_translate("Form", "TextLabel"))
        self.label.setText(_translate("Form", "09:02"))
        self.label_6.setText(_translate("Form", "个人识别信息"))
        self.label_2.setText(_translate("Form", "学号："))
        self.lbID.setText(_translate("Form", "TextLabel"))
        self.label_7.setText(_translate("Form", "姓名："))
        self.lbName.setText(_translate("Form", "TextLabel"))
        self.label_4.setText(_translate("Form", "学院："))
        self.lbCollege.setText(_translate("Form", "TextLabel"))
        self.lb600.setText(_translate("Form", "专业："))
        self.lbMajor.setText(_translate("Form", "TextLabel"))
        self.label_3.setText(_translate("Form", "体温："))
        self.lbTempera.setText(_translate("Form", "TextLabel"))
        self.label_8.setText(_translate("Form", "健康码："))
        self.lbStatus.setText(_translate("Form", "TextLabel"))

    # 更新时间
    def getDate(self):
        now = QDate.currentDate()
        datetime = QDateTime.currentDateTime()
        time = QTime.currentTime()
        self.label_10.setText(now.toString()[0:2])
        self.label_9.setText(now.toString("yyyy/MM/dd"))
        self.label.setText(time.toString("HH:mm"))
        now.toString()[0:2]

    # 更新验证的图像
    def getFaceImg(self, path):
        self.lbBckImg.setPixmap(QtGui.QPixmap(path))
        self.lbBckImg.setScaledContents(True)

    # 更新显示信息 id: 编号  wd： 温度 status: 状态
    def updateShowInfo(self, post):
        self.lbID.setText(post['studentId'])
        self.lbName.setText(post['studentName'])
        self.lbCollege.setText(post['college'])
        self.lbMajor.setText(post['className'])
        self.lbTempera.setText(post['temperature'])
        self.lbStatus.setText(post['healthCode'])
        # self.lbID.setText(id)
        # self.lbName.setText(name)
        # self.lbCollege.setText(college)
        # self.lbMajor.setText(major)
        # self.lbTempera.setText(wd)
        # self.lbStatus.setText(status)

    # 更新显示图像 imgPath：显示图像的路径
    def updateShowImg(self, imgPath):
        self.lbShowImg.setPixmap(QtGui.QPixmap(imgPath))
        self.lbShowImg.setScaledContents(True)

    # 更新提示信息 msg: 提示信息
    def updateInfo(self, msg):
        self.lbShowInfo.setText(msg)

    # 设置图标
    def setIcon(self, msg):
        self.lbShowImg.setPixmap(QtGui.QPixmap(msg))
        self.lbShowImg.setScaledContents(True)

    # 显示视频
    def showVideo(self):
        ret, frame = self.cap.read()
        # ret = 0
        if ret:
            show = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            showImage = QImage(show.data, show.shape[1], show.shape[0], QImage.Format_RGB888)
            self.lbShowMainImg.setPixmap(QPixmap.fromImage(showImage))
            self.lbShowMainImg.setScaledContents(True)
            if self.count == 20:
                # 速度太慢 画面卡顿
                # self.flag = faceDetection(frame)
                # print(self.flag)
                cv2.imwrite('faceImage.jpg', frame)
                self.count = 0
            self.count += 1
        else:
            pathCapFail = "image/state04.png"
            self.lbBckImg.setPixmap(QtGui.QPixmap(pathCapFail))
            self.lbBckImg.setScaledContents(True)
            curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
            f = open('Log.txt', 'a')
            f.write("摄像头未连接..." + "     " + "Time:" + str(curren_time) + '\n')
            f.close()

