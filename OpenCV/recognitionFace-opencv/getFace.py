'''

本程序用于产生50张灰度图片素材用于后续训练人脸识别系统

'''
import cv2
import os

face_xml_location=os.path.join('.','haarcascade_frontalface_default.xml')
detector = cv2.CascadeClassifier(face_xml_location)
camera = cv2.VideoCapture(0)
pic_num = 0
ID = input('enter your id: ')

while True:
    ret, img = camera.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = detector.detectMultiScale(gray,1.3, 5)
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
        pic_num = pic_num + 1
        pic_save_location=os.path.join('.', 'faceData', 'face',  'user%s.%s.jpg')
        cv2.imwrite(pic_save_location%(ID,pic_num), gray[y:y + h, x:x + w])
        cv2.imshow('frame', img)
    # 设置相片取样间隔
    if cv2.waitKey(100) & 0xFF == ord('q'):
        break
    # 设置采样相片数
    elif pic_num > 50:
        break

camera.release()
cv2.destroyAllWindows()
