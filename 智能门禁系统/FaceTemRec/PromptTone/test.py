# https://www.piwheels.org/simple/opencv-python/opencv_python-3.4.6.27-cp37-cp37m-linux_armv7l.whl
from PyQt5 import QtMultimedia
from PyQt5.QtCore import QUrl
def playRecord(path):
    file = QUrl.fromLocalFile(path) # 音频文件路径
    content = QtMultimedia.QMediaContent(file)
    player.setMedia(content)
    player.setVolume(50.0)
    player.play()

if __name__ == '__main__':
    path = '/home/pi/codes/PromptTone/AbnTem.m4a'
    playRecord(path)