from keras.applications.vgg16 import VGG16
from keras.layers import Input, Dense, Flatten, Conv2D, BatchNormalization, MaxPooling2D, Dropout
from keras.models import Model
import numpy as np
import load_data
import random
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtGui import QImage,QPixmap
import cv2
import EyeSignal


def prepare_data(file):
    X, Y = load_data.get_data(file)
    # print('total images:{0}'.format(len(X)))
    return X, Y


def predict_mean_metrics(img,dictionary):

    X = np.asarray(img, dtype=np.float32)
    X=np.expand_dims(X,0)
    X -= np.array([111.40537, 120.87209, 136.82808])
    X /= np.array([43.77899962, 43.45094616, 49.08783324])
    result = model.predict(X)
    result = np.argmax(result, axis=1)
    result=dictionary[str(result[0])]
    return result



def vgg_model():
    base_model = VGG16(include_top=False, weights=None, input_shape=(200, 400, 3))
    x = Flatten(name='flatten')(base_model.output)
    x = Dense(4096, activation='relu', name='fc1')(x)
    x = Dense(4096, activation='relu', name='fc2')(x)
    x = Dense(6, activation='softmax', name='pred')(x)
    model = Model(inputs=base_model.input, outputs=x)
    model.load_weights('./weights/checkpoint.h5', by_name=True)
    return model


def cvimg_to_qtimg(cvimg):
    height, width, depth = cvimg.shape
    cvimg = cv2.cvtColor(cvimg, cv2.COLOR_BGR2RGB)
    cvimg = QImage(cvimg.data, width, height, width * depth, QImage.Format_RGB888)

    return cvimg


def show_video():
    cap = cv2.VideoCapture(0)
    h, w = 200, 400
    y_offset, x_offset = 100, 120
    ls = 1
    ui.label_2.resize(w, h)
    dictionary={'0':'accelerate','1':'decelerate','2':'turn left','3':'turn right','4':'start','5':'stop'}
    while True:
        # Capture frame-by-frame
        ret, frame = cap.read()
        frame = cv2.flip(frame, 1)
        cv2.rectangle(frame, (x_offset, y_offset), (x_offset + w, y_offset + h), (0, 0, 255), ls)
        frame_cut = frame[y_offset:y_offset + h, x_offset:x_offset + w]
        image = cvimg_to_qtimg(frame_cut)
        ui.label_2.setPixmap(QPixmap(image).scaled(ui.label_2.width(), ui.label_2.height()))
        result=predict_mean_metrics(frame_cut,dictionary)
        ui.textEdit.setText(result)
        # Display the resulting frame
        # cv2.imshow('frame', frame)
        c = cv2.waitKey(30) & 0xff
        if c == 27:
            cap.release()
            break


if __name__ == "__main__":
    model = vgg_model()
    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    ui = EyeSignal.Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    ui.OpenCamera.clicked.connect(show_video)
    sys.exit(app.exec_())

