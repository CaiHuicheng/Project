import serial
import time  # 延时使用
import binascii

s = serial.Serial("COM5", 9600)  # 初始化串口


def thermometry(s):
    count = 0
    temSum = 0.0
    checkTem = ''
    Hex_str = bytes.fromhex('aa bb 22 22')  # 文本转换Hex
    while count < 3:
        temD = 0.0
        # =bytes.fromhex('aa bb 22 22')
        s.write(Hex_str)  # 串口发送 Hex_str()
        # 接收
        n = s.inWaiting()  # 串口接收
        try:
            if n:
                data = str(binascii.b2a_hex(s.read(n)))[2:-1]  # Hex转换成字符串
                # print(data)  # 字符串输出
                checkTem = data[0:4]
                # print(data)
                if checkTem == 'aaaa':
                    temhex_h = data[8:10]
                    temhex_l = data[6:8]
                    # print(type(checkTem),checkTem)  # 字符串输出
                    temhexStr = '0x' + temhex_h + temhex_l
                    # print(float(temhex_str))
                    temHexToD = int(temhexStr, 16)
                    temD = (temHexToD - 400) / 10
                    # print("%s -> %s",temhexStr,temD)
        except Exception:
            continue
        if 30 <= temD <= 40:
            temSum += temD
            print(temD)
            count = count + 1
        else:
            continue
        time.sleep(1)
        print(count)
    print(temSum)
    averageTem = (temSum / 3)
    return format(averageTem, '.1f')


if __name__ == '__main__':
    time_start = time.time()
    tem = thermometry(s)
    print(tem)
    time_end = time.time()
    print(time_end - time_start)
    exit()
