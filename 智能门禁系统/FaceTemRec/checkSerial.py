#!/usr/bin/python
#coding:utf-8
"""
获取串口，检测串口是否连接 linux下函数
"""
import serial
import serial.tools.list_ports
import os


def checkSerial():
    # print('S')
    try:
        plist = list(serial.tools.list_ports.comports())
        plist_0 = list(plist[0])
        serialName = plist_0[0]
        name = serialName.split('/')[2]
        # print(name[0:6])
        if name[0:6] != 'ttyUSB':
            return True
        else:
            return False
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write(" checkSerial.py Function Error >>checkSerial:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return False


if __name__ == '__main__':
    print(checkSerial())