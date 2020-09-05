#!/usr/bin/python
#coding:utf-8
import json
import time
import requests
import os


def postData(stuNum, phoneNum, Tem, deviceNum, mac):
    # print('postData')
    # url = 'http://httpbin.org/post'
    url = 'https://47.97.204.64:8443/terminal/pass/state'
    headers = {'content-type': 'application/json'}
    d = json.dumps({'studentId': stuNum, 'phone': phoneNum, 'temperature': Tem, 'deviceId': deviceNum, 'macId': mac})
    try:
        post = requests.post(url, data=d, verify=False, headers=headers,timeout = (2,4))
    except Exception as e:
        curren_time = time.asctime(time.localtime(time.time()))  # 获取当前时间
        f = open(os.getcwd()+'/Log.txt', 'a')
        f.write("网络未连接..." + str(e) + "     " + "Time:" + str(curren_time) + '\n')
        f.close()
        return 0
    content = json.loads(post.text)
    data = content['data']
    # print('返回数据：', data)
    try:
        if int(data['studentId']):
            postData = data
    except Exception:
        postData = {'studentId': stuNum, 'college': '---', 'studentName': '---', 'temperature': data['temperature'], 'className': '---', 'healthCode': data['healthCode']}
    # netlink=jsonpath.jsonpath(content,'$..tracking_url')
    # return netlink
    if content['msg'] == '请求成功':
        return postData
    else:
        return 0


if __name__ == '__main__':
    post = postData('1811610029', '18258618917', '35.5', '1000001', 'dc:a6:32:01:4f:1d')
    # print(post['temperature'],post['healthCode'])
    # print(post['studentId'])
    print(post)
