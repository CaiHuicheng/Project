import requests
url = 'http://httpbin.org/post'
d = {'id': '1711610035', 'temperature': '36.8'}
r = requests.post(url, data=d)
print(r.text) 