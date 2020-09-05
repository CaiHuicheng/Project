#!/usr/bin/python
#coding:utf-8
import RPi.GPIO as GPIO
import time                #导入延时函数

def controlDoor(choice):
    if choice=="OPEN":         
        print('open door')
        GPIO.setmode(GPIO.BCM)     # 使用BCM编码
        GPIO.setup(25,GPIO.OUT)    # 使用BCM编码的25号脚
        GPIO.output(25,GPIO.HIGH)  # 输出高电平,打开门
    elif choice=="CLOSE":         
        print('close door')
        GPIO.output(25,GPIO.LOW)   # 输出低电平,关闭门
        GPIO.cleanup()             # 退出,释放资源
    
if __name__ == '__main__':
    i=0
    while True:
        time.sleep(5)              # 模拟识别程序
        controlDoor('OPEN')
        time.sleep(3)              # 开门时间
        controlDoor('CLOSE')
        i += 1
        if i>=2:
            break