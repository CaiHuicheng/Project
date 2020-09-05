#!/usr/bin/python
#coding:utf-8

import serial
import string
import binascii
s=serial.Serial('/dev/ttyUSB0',9600)
#发送
d=bytes.fromhex('10 11 12 34 3f') 
s.write(d)
#接收
n=s.inwaiting()
if n: 
    data= str(binascii.b2a_hex(s.read(n)))[2:-1]
    print(data)
s.close()