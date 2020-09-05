import requests
import json
def postData(ID,Tem):
    url = 'http://httpbin.org/post'
    # url = 'https://47.97.204.64:8443/terminal/pass/state/post'
    d = json.dumps({'id': ID, 'temperature': Tem})
    post = requests.post(url, data=d)
    print(post)
    print(post.text)

if __name__ == '__main__':
    postData('171161','37.0')
