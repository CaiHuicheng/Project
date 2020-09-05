import serial
import time  # 延时使用
import binascii

s = serial.Serial("COM5", 9600)  # 初始化串口

count = 0
temTreeSum = 0.0

while count < 3:
    temSum = 0.0
    Hex_str = bytes.fromhex('aa bb 22 22')  # 文本转换Hex
    # =bytes.fromhex('aa bb 22 22')
    s.write(Hex_str)  # 串口发送 Hex_str()
    # 接收
    n = s.inWaiting()  # 串口接收
    try:
        if n:
            data = str(binascii.b2a_hex(s.read(n)))[2:-1]  # Hex转换成字符串
            checkTem = data[0:4]
            temhex_h = data[8:10]
            temhex_l = data[6:8]
            print(checkTem)  # 字符串输出
            if checkTem == "aaaa":
                temhexStr = temhex_h + temhex_l
                # print(temhexStr)
                # print(float(temhex_str))
                # print(int(temhexStr, 16))
                temSum = (int(temhexStr, 16) - 400) / 10
                if 35 <= temSum <= 40:
                    temTreeSum += temSum
                    count += 1
                    print(count)
                print(temSum)
    except Exception:
        continue
    time.sleep(0.01)


print(temSum)
averageTem = (temSum / 3)
print(averageTem)