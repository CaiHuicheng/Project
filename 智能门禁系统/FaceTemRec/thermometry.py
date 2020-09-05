#!/usr/bin/python
#coding:utf-8
# 通过串口获取红外测温模块数据

import serial
import time  # 延时使用
import binascii
import serial.tools.list_ports
import os
import threading
plist = list(serial.tools.list_ports.comports())
plist_0 = list(plist[0])
serialName = plist_0[0]

# def breakTime():
#     t = threading.Timer(4,thermometry)
#     t.start()


def thermometry():
    # breakTime()
    try:
        # s = serial.Serial("COM5", 9600)
        s = serial.Serial(serialName, 9600, timeout=1)
        if s.isOpen():
            s.flushInput()  # 清空缓冲区
            count = 0
            temSum = 0.0
            checkTem = ''
            # print(s)
    #         Hex_str = bytes.fromhex('aa bb 22 22')  # 文本转换Hex
            Hex_str = bytes.fromhex('aa bb 22 22')
    #         s.write(Hex_str)
            while count < 1:
                temD = 0.0
                # =bytes.fromhex('aa bb 22 22')
                # Hex_str = bytes.fromhex('aa bb f1 f1')  # 文本转换Hex
                s.write(Hex_str)  # 串口发送 Hex_str()
                # 接收
                n = s.inWaiting()  # 串口接收
                # print(n)
                try:
                    if n:
                        data = str(binascii.b2a_hex(s.read(n)))[2:20]  # Hex转换成字符串
                        # print(data)
                        checkTem = data[0:4]
                        # print(checkTem)
                        if checkTem == 'aaaa':
                            # 旧测温模块
    #                         temhex_h = data[8:10]
    #                         temhex_l = data[6:8]
                            temhex_h = data[12:14]
                            temhex_l = data[10:12]
                            # print(type(checkTem),checkTem)  # 字符串输出
                            temhexStr = '0x' + temhex_h + temhex_l
                            # print(float(temhex_str))
                            temHexToD = int(temhexStr, 16)
                            temD = (temHexToD-400) / 10
                            # print("%s -> %s",temhexStr,temD)
                except Exception:
                    continue
                if 20 <= temD <= 60:
                    temSum += temD
                else:
                    continue
                count = count + 1
                time.sleep(0.1)
                # print(count)
            # print(temSum)
            averageTem = (temSum / 1)
            s.close()  # 关闭串口
            return format(averageTem, '.1f')
        else:
            return 0 
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("thermometry.py function Error >>thermometry:" + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return 0


if __name__ == '__main__':
    while True:
        time_start = time.time()
        tem = thermometry()
        print(tem)
        time_end = time.time()
        print(time_end - time_start)
    exit()
