#!/usr/bin/python
#coding:utf-8
import datetime
import os
import time

# ........init........
abs_file = __file__
# .........endinit........th

timeStamp1 = time.time()
# timeStamp2 = time.time()+604800
# timeStamp2 = time.time()+2592000


def ClearFile():
    try:
        # 文件夹路径
        # path = abs_file[:abs_file.rfind('/')]
        path = os.getcwd() + '/Log.txt'
        # path = os.getcwd() + '\Log.txt'
        # print(path)
        suffix = "txt"  # 需要删除的文件类型 suffix= “”填空表示所有文件
        if os.path.isfile(path):
            # print(os.path.isfile(path))
            statInfo = os.stat(path)
            timeFlag = timeStamp1-(statInfo.st_ctime+2592000)
            fileSize = os.path.getsize(path)
            # print(statInfo)
            # print(fileSize)
            if timeFlag >= 0 or fileSize > 500*1024*1024:
                if path.endswith(suffix):
                    # print(path)  # 打印显示查找的后缀文件
                    f = open(path, "r+")
                    f.truncate()
                    f.close()
                    # os.remove(dir)  # 取消注释后删除查找的所有文件
            return True
        else:
            return False
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("timeDeleteFile.py Function Error >>QThread2 run:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return False


if __name__ == '__main__':
    date1 = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))  # 起始时间 注意:起始时间必须在2000年以后
    print(date1)
    fileList = ClearFile()
