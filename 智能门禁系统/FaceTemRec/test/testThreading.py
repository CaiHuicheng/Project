from thermometry import thermometry
from testAPI import *
from threading import Thread
import time
from picamera import PiCamera
from testRequests import postData

"""重新定义带返回值的线程类"""
class ThreadReturn(Thread):
    def __init__(self, func_list):
        super(ThreadReturn, self).__init__()
        self.func_list = func_list

    def run(self):
        self.result = self.func_list()

    def get_result(self):
        try:
            r = self.result
            return r
        except Exception:
            return None


#threads = []
#threads.addend(threading.Thread(target = faceRecognition()))
#threads.addend(threading.Thread(target = thermometry()))



if __name__ == '__main__':
    time_start = time.time()
    faceID = ThreadReturn(faceRecognition)
    tem = ThreadReturn(thermometry)
    faceID.start()
    tem.start()
    faceID.join()
    tem.join()
    ID = faceID.get_result()
    Tem = tem.get_result()
    print("ID:%s  温度：%s"%(ID,Tem))
    if faceID:
        postData(ID,Tem)
    time_end = time.time()
    print (time_end - time_start)
    # camera.stop_preview()#结束摄像
    exit()


