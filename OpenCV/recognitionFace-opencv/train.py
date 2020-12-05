import cv2
import os
import numpy as np
from PIL import Image

face_xml_location=os.path.join('.','haarcascade_frontalface_default.xml')
detector = cv2.CascadeClassifier(face_xml_location)
recognizer = cv2.face.LBPHFaceRecognizer_create()


def get_images_and_labels(path):
    image_paths = [os.path.join(path, f) for f in os.listdir(path)]
    face_samples = []
    ids = []

    for image_path in image_paths:
        image = Image.open(image_path).convert('L')
        image_np = np.array(image, 'uint8')
        if os.path.split(image_path)[-1].split(".")[-1] != 'jpg':
            continue
        image_id = int(os.path.split(image_path)[-1].split(".")[1])
        faces = detector.detectMultiScale(image_np)
        for (x, y, w, h) in faces:
            face_samples.append(image_np[y:y + h, x:x + w])
            ids.append(image_id)

    return face_samples, ids

tain_data_location=os.path.join('.', 'faceData', 'data', 'train.yml')
face_data_location=os.path.join('.', 'faceData', 'face')
faces, Ids = get_images_and_labels(face_data_location)
recognizer.train(faces, np.array(Ids))
recognizer.save(tain_data_location)

