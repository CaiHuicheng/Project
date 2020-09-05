# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'mainWindow.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

#导入cv
import cv2
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtCore import QDate, QTime, QDateTime, Qt, QTimer
from PyQt5.QtGui import QPalette, QBrush, QPixmap, QImage
class Ui_Form(QWidget):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.setWindowTitle("")
        # Form.setfix(391, 464)

        Form.setMinimumSize(QtCore.QSize(680, 800))
        Form.setMaximumSize(QtCore.QSize(680, 800))
        self.verticalLayout = QtWidgets.QVBoxLayout(Form)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.label = QtWidgets.QLabel(Form)
        self.label.setMinimumSize(QtCore.QSize(0, 40))
        self.label.setMaximumSize(QtCore.QSize(16777215, 40))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setObjectName("label")

        self.labelLeft = QtWidgets.QLabel(Form)
        self.labelLeft.setMinimumSize(QtCore.QSize(0, 40))
        self.labelLeft.setMaximumSize(QtCore.QSize(16777215, 40))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.labelLeft.setFont(font)
        self.labelLeft.setAlignment(QtCore.Qt.AlignRight|QtCore.Qt.AlignTrailing|QtCore.Qt.AlignVCenter)
        self.labelLeft.setObjectName("labelLeft")

        self.lay = QtWidgets.QHBoxLayout()
        self.lay.setContentsMargins(6,0,6,0)
        self.lay.setSpacing(0)
        self.lay.addWidget(self.label)
        self.lay.addWidget(self.labelLeft)

        self.verticalLayout.addLayout(self.lay)
        self.frame = QtWidgets.QFrame(Form)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.frame.sizePolicy().hasHeightForWidth())
        self.frame.setSizePolicy(sizePolicy)
        self.frame.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame.setObjectName("frame")
        self.verticalLayout_8 = QtWidgets.QVBoxLayout(self.frame)
        self.verticalLayout_8.setObjectName("verticalLayout_8")
        self.verticalLayout_8.setContentsMargins(0,0,0,0)
        #显示图像
        self.lbShowMainImg = QtWidgets.QLabel(self.frame)
        self.lbShowMainImg.setText("")
        self.lbShowMainImg.setObjectName("lbShowMainImg")
        self.verticalLayout_8.addWidget(self.lbShowMainImg)
        self.verticalLayout.addWidget(self.frame)
        #添加面部背景
        self.lbBckImg = QtWidgets.QLabel(self.lbShowMainImg)
        self.lbBckImg.setSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)

        self.lbBckImg.setPixmap(QtGui.QPixmap("bck.png"))
        self.lbBckImg.setScaledContents(True)
        #将面部背景添加到界面中
        self.lbBckImgLayout = QtWidgets.QVBoxLayout(self.lbShowMainImg)
        self.lbBckImgLayout.setContentsMargins(0,0,0,0)
        self.lbShowMainImg.setLayout(self.lbBckImgLayout)
        self.lbBckImgLayout.setObjectName("lbBckImgLayout")
        self.lbBckImgLayout.addWidget( self.lbBckImg)

        self.horizontalLayout = QtWidgets.QHBoxLayout()
        # self.horizontalLayout.setContentsMargins(0,0,0,0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.frame_4 = QtWidgets.QFrame(Form)
        self.frame_4.setMinimumSize(QtCore.QSize(0, 200))
        self.frame_4.setMaximumSize(QtCore.QSize(16777215, 200))
        self.frame_4.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_4.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_4.setObjectName("frame_4")
        self.verticalLayout_5 = QtWidgets.QVBoxLayout(self.frame_4)
        self.verticalLayout_5.setObjectName("verticalLayout_5")
        self.groupBox_2 = QtWidgets.QGroupBox(self.frame_4)
        self.groupBox_2.setObjectName("groupBox_2")
        self.verticalLayout_6 = QtWidgets.QVBoxLayout(self.groupBox_2)
        self.verticalLayout_6.setObjectName("verticalLayout_6")
        #显示图像
        self.lbShowImg = QtWidgets.QLabel(self.groupBox_2)
        self.lbShowImg.setText("")
        self.lbShowImg.setObjectName("lbShowImg")
        self.verticalLayout_6.addWidget(self.lbShowImg)
        self.verticalLayout_5.addWidget(self.groupBox_2)
        self.horizontalLayout.addWidget(self.frame_4)
        self.frame_2 = QtWidgets.QFrame(Form)
        self.frame_2.setMinimumSize(QtCore.QSize(0, 200))
        self.frame_2.setMaximumSize(QtCore.QSize(16777215, 200))
        self.frame_2.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_2.setObjectName("frame_2")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.frame_2)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.groupBox = QtWidgets.QGroupBox(self.frame_2)
        self.groupBox.setObjectName("groupBox")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.groupBox)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.label_2 = QtWidgets.QLabel(self.groupBox)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout_4.addWidget(self.label_2)
        self.lbID = QtWidgets.QLabel(self.groupBox)
        self.lbID.setObjectName("lbID")
        self.horizontalLayout_4.addWidget(self.lbID)
        self.verticalLayout_4.addLayout(self.horizontalLayout_4)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        #姓名
        self.horizontalLayout_12 = QtWidgets.QHBoxLayout()
        self.label_12 = QtWidgets.QLabel(self.groupBox)
        self.label_12.setObjectName("label_12")
        self.lbName = QtWidgets.QLabel(self.groupBox)
        self.lbName.setObjectName("lbName")
        self.horizontalLayout_12.addWidget(self.label_12)
        self.horizontalLayout_12.addWidget(self.lbName)
        self.verticalLayout_4.addLayout(self.horizontalLayout_12)
        # 学院
        self.horizontalLayout_13 = QtWidgets.QHBoxLayout()
        self.label_13 = QtWidgets.QLabel(self.groupBox)
        self.label_13.setObjectName("label_13")
        self.lbCollege = QtWidgets.QLabel(self.groupBox)
        self.lbCollege.setObjectName("lbCollege")
        self.horizontalLayout_13.addWidget(self.label_13)
        self.horizontalLayout_13.addWidget(self.lbCollege)
        self.verticalLayout_4.addLayout(self.horizontalLayout_13)
        #专业
        self.horizontalLayout_14 = QtWidgets.QHBoxLayout()
        self.label_14 = QtWidgets.QLabel(self.groupBox)
        self.label_14.setObjectName("label_14")
        self.lbMajor = QtWidgets.QLabel(self.groupBox)
        self.lbMajor.setObjectName("lbMajor")
        self.horizontalLayout_14.addWidget(self.label_14)
        self.horizontalLayout_14.addWidget(self.lbMajor)
        self.verticalLayout_4.addLayout(self.horizontalLayout_14)

        self.label_3 = QtWidgets.QLabel(self.groupBox)
        self.label_3.setObjectName("label_3")
        self.horizontalLayout_3.addWidget(self.label_3)
        self.lbTempera = QtWidgets.QLabel(self.groupBox)
        self.lbTempera.setObjectName("lbTempera")
        self.horizontalLayout_3.addWidget(self.lbTempera)
        self.verticalLayout_4.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label_4 = QtWidgets.QLabel(self.groupBox)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_2.addWidget(self.label_4)
        self.lbStatus = QtWidgets.QLabel(self.groupBox)
        self.lbStatus.setObjectName("lbStatus")
        self.horizontalLayout_2.addWidget(self.lbStatus)
        self.verticalLayout_4.addLayout(self.horizontalLayout_2)
        self.verticalLayout_3.addWidget(self.groupBox)
        self.horizontalLayout.addWidget(self.frame_2)
        self.frame_5 = QtWidgets.QFrame(Form)
        self.frame_5.setMinimumSize(QtCore.QSize(0, 200))
        self.frame_5.setMaximumSize(QtCore.QSize(16777215, 200))
        self.frame_5.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.frame_5.setFrameShadow(QtWidgets.QFrame.Raised)
        self.frame_5.setObjectName("frame_5")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.frame_5)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.groupBox_3 = QtWidgets.QGroupBox(self.frame_5)
        self.groupBox_3.setObjectName("groupBox_3")
        self.verticalLayout_7 = QtWidgets.QVBoxLayout(self.groupBox_3)
        self.verticalLayout_7.setObjectName("verticalLayout_7")
        self.lbShowInfo = QtWidgets.QLabel(self.groupBox_3)
        self.lbShowInfo.setAlignment(QtCore.Qt.AlignCenter)
        self.lbShowInfo.setObjectName("lbShowInfo")
        self.verticalLayout_7.addWidget(self.lbShowInfo)
        self.verticalLayout_2.addWidget(self.groupBox_3)
        self.horizontalLayout.addWidget(self.frame_5)
        self.verticalLayout.addLayout(self.horizontalLayout)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

        self.timer_camera = QTimer(self)
        #拍照
        self.cap = cv2.VideoCapture(0)
        #1s 40帧图像
        self.timer_camera.timeout.connect(self.showVideo)
        self.timer_camera.start(25)

        #显示时间
        self.timer = QTimer()
        self.timer.timeout.connect(self.getDate)
        self.timer.start(1000)

        #调用更新显示更新显示信息调用
        self.updateShowInfo("---", "---", "---", "---", "---", "---")

        #调用更新显示图像
        self.updateShowImg("bck.png")

        #调用更新提示信息
        self.updateInfo("无提示")

        #更新人脸识别图像
        # self.getFaceImg("yt3.jpg")

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        # self.label.setText(_translate("Form", "时间：星期一"))
        self.groupBox_2.setTitle(_translate("Form", "图片"))
        self.groupBox.setTitle(_translate("Form", "显示信息"))
        self.label_2.setText(_translate("Form", "编号："))

        self.label_12.setText(_translate("Form", "姓名："))
        self.lbName.setText(_translate("Form", "张三"))
        self.label_13.setText(_translate("Form", "学院："))
        self.lbCollege.setText(_translate("Form", "自动化学院"))
        self.label_14.setText(_translate("Form", "专业："))
        self.lbMajor.setText(_translate("Form", "土木工程"))
        self.lbID.setText(_translate("Form", "TextLabel"))
        self.label_3.setText(_translate("Form", "体温："))
        self.lbTempera.setText(_translate("Form", "TextLabel"))
        self.label_4.setText(_translate("Form", "状态："))
        self.lbStatus.setText(_translate("Form", "TextLabel"))
        self.groupBox_3.setTitle(_translate("Form", "提示信息"))
        self.lbShowInfo.setText(_translate("Form", "提示信息"))

    #更新时间
    def getDate(self):
        now = QDate.currentDate()
        datetime = QDateTime.currentDateTime()
        self.label.setText(datetime.toString("yyyy/MM/dd HH:mm:ss"))
        self.labelLeft.setText(now.toString()[0:2])

    #更新验证的图像
    def getFaceImg(self, path):
        self.lbShowMainImg.setPixmap(QtGui.QPixmap(path))
        self.lbShowImg.setScaledContents(False)

    #更新显示信息 id: 编号  wd： 温度 status: 状态
    def updateShowInfo(self, id, name, college, major,  wd, status):
        self.lbID.setText(id)
        self.lbName.setText(name)
        self.lbCollege.setText(college)
        self.lbMajor.setText(major)
        self.lbTempera.setText(wd)
        self.lbStatus.setText(status)

    #更新显示图像 imgPath：显示图像的路径
    def updateShowImg(self, imgPath):
        self.lbShowImg.setPixmap(QtGui.QPixmap(imgPath))
        self.lbShowImg.setScaledContents(False)

    #更新提示信息 msg: 提示信息
    def updateInfo(self, msg):
        self.lbShowInfo.setText(msg)

    #显示视频
    def showVideo(self):
        ret, frame = self.cap.read()
        show = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        showImage = QImage(show.data, show.shape[1], show.shape[0], QImage.Format_RGB888)
        self.lbShowMainImg.setPixmap(QPixmap.fromImage(showImage))
        self.lbShowMainImg.setScaledContents(False)

