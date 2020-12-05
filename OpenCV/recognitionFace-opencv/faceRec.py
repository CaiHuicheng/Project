import cv2
import numpy as np
import os

recognizer = cv2.face.LBPHFaceRecognizer_create()
train_data_location=os.path.join('.','faceData','data','train.yml')
recognizer.read(train_data_location)

face_xml_location=os.path.join('.','haarcascade_frontalface_default.xml')
face_cascade = cv2.CascadeClassifier(face_xml_location)
camera = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_SIMPLEX

while True:
    ret, im = camera.read()
    gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, 1.2, 5)
    for (x, y, w, h) in faces:
        cv2.rectangle(im, (x - 50, y - 50), (x + w + 50, y + h + 50), (225, 0, 0), 2)
        img_id, conf = recognizer.predict(gray[y:y + h, x:x + w])
        if conf > 50:
            if img_id <50:
                img_id = '1711610035'
        else:
            img_id = "Unknown"
        cv2.putText(im, str(img_id), (x, y + h), font, 0.55, (0, 255, 0), 1)
    cv2.imshow('im', im)
    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

camera.release()
cv2.destroyAllWindows()

