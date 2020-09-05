from thermometry import thermometry
from testAPI import *
from threading import Thread
import time
from picamera import PiCamera
from testRequests import postData


time_start = time.time()
faceID = faceRecognition()
if faceID:
    tem = thermometry()
    print("ID:%s  温度：%s"%(faceID,tem))
    postData(faceID,tem)
time_end = time.time()
print (time_end - time_start)
# camera.stop_preview()#结束摄像
exit()
