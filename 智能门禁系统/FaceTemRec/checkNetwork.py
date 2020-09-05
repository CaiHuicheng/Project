#!/usr/bin/python
#coding:utf-8
"""
checkCap:检测网络是否链接正常
"""
import time
import os

def isConnected():
    # print('Net')
    import requests
    try:
        html = requests.get("http://www.baidu.com", timeout=2)
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("网络未连接..." + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return True
    return False


if __name__ == '__main__':
    print(isConnected())
