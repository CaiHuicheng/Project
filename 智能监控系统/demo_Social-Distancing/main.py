import time
import math

from threading import *

from multiprocessing import Lock
from cameraCalibration import *
from playRecording import *
import cv2
import os
import numpy as np


video_name = "video02.mp4"
vid_path = "./videos/"+video_name


labelsPath = "./coco.names"

LABELS = open(labelsPath).read().strip().split("\n")

np.random.seed(42)

weightsPath = "./yolov3.weights"
configPath = "./yolov3.cfg"


# weightsPath = "./yolov3-tiny.weights"  ## https://pjreddie.com/media/files/yolov3-tiny.weights
# configPath = "./yolov3-tiny.cfg"       ## https://github.com/pjreddie/darknet/blob/master/cfg/yolov3-tiny.cfg


net = cv2.dnn.readNetFromDarknet(configPath, weightsPath)
ln = net.getLayerNames()
ln = [ln[i[0] - 1] for i in net.getUnconnectedOutLayers()]

vs = cv2.VideoCapture(vid_path)
vs.set(cv2.CAP_PROP_FRAME_WIDTH, 640)  # 设置宽度
vs.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)  # 设置长度
# vs = cv2.VideoCapture(0)  # 摄像头读取数据
fl = 0
q = 0
FR = 0
# 显示视频流信号量
mutex = 0


class ShowVideo(Thread):
    def __init__(self):
        Thread.__init__(self)
        self.count = 0

    def run(self):
        global mutex
        while True:
            try:
                time_start = time.time()
                cv2.namedWindow("show_monitoring", cv2.WINDOW_NORMAL)
                cv2.resizeWindow("show_monitoring",1024,640)
                (grabbed, video_frame) = vs.read()
                if not grabbed:
                    cv2.destroyWindow("show_monitoring")
                    os.remove("detectionFrame.jpg")
                    continue
                if mutex == 0:
                    cv2.imshow('show_monitoring', video_frame)
                    cv2.waitKey(1)
                else:
                    try:
                        time.sleep(0.3)
                        frame = cv2.imread("detectionFrame.jpg")
                        cv2.imshow("show_monitoring", frame)
                        PlayRecording("./music/01.mp3")
                        pygame.mixer.music.play()
                        cv2.waitKey(3000)
                        pygame.mixer.music.stop()
                        os.remove("detectionFrame.jpg")
                    except Exception as e:
                        print(e)
                        cv2.imshow('show_monitoring', video_frame)
                        cv2.waitKey(1)
                    mutex = 0
                if self.count == 30:
                    print('30帧')
                    cv2.imwrite("detectionFrame.jpg", video_frame)
                    self.count = 0
                    time_load = time.time()
                    print('loadTime:', time_load - time_start)
                self.count += 1
            except Exception as e:
                print(e)


class DetectionFrame(Thread):
    def __init__(self):
        Thread.__init__(self)

    def run(self):
        global mutex
        while True:
            try:
                flag = 0
                (W, H) = (None, None)
                try:
                    frame = cv2.imread("detectionFrame.jpg")
                except Exception as e:
                    cv2.destroyWindow("show_detection")
                    print(e)
                    break
                if W is None or H is None:
                    (H, W) = frame.shape[:2]
                    FW = W
                    if (W < 1075):
                        FW = 1075
                    FR = np.zeros((H + 210, FW, 3), np.uint8)

                    col = (255, 255, 255)
                    FH = H + 210
                FR[:] = col

                blob = cv2.dnn.blobFromImage(frame, 1 / 255.0, (416, 416),
                                             swapRB=True, crop=False)
                net.setInput(blob)
                layerOutputs = net.forward(ln)

                boxes = []
                confidences = []
                classIDs = []

                for output in layerOutputs:

                    for detection in output:

                        scores = detection[5:]
                        classID = np.argmax(scores)
                        confidence = scores[classID]
                        if LABELS[classID] == "person":

                            if confidence > confid:
                                box = detection[0:4] * np.array([W, H, W, H])
                                (centerX, centerY, width, height) = box.astype("int")

                                x = int(centerX - (width / 2))
                                y = int(centerY - (height / 2))

                                boxes.append([x, y, int(width), int(height)])
                                confidences.append(float(confidence))
                                classIDs.append(classID)

                idxs = cv2.dnn.NMSBoxes(boxes, confidences, confid, thresh)

                if len(idxs) > 0:
                    status = []
                    idf = idxs.flatten()
                    close_pair = []
                    s_close_pair = []
                    center = []
                    co_info = []

                    for i in idf:
                        (x, y) = (boxes[i][0], boxes[i][1])
                        (w, h) = (boxes[i][2], boxes[i][3])
                        cen = [int(x + w / 2), int(y + h / 2)]
                        center.append(cen)
                        cv2.circle(frame, tuple(cen), 1, (0, 0, 0), 1)
                        co_info.append([w, h, cen])

                        status.append(0)
                    for i in range(len(center)):
                        for j in range(len(center)):
                            g = isclose(co_info[i], co_info[j])
                            if g == 1:
                                close_pair.append([center[i], center[j]])
                                status[i] = 1
                                status[j] = 1
                            elif g == 2:
                                s_close_pair.append([center[i], center[j]])
                                if status[i] != 1:
                                    status[i] = 2
                                if status[j] != 1:
                                    status[j] = 2
                    total_p = len(center)
                    low_risk_p = status.count(2)
                    high_risk_p = status.count(1)
                    safe_p = status.count(0)
                    kk = 0
                    for i in idf:
                        cv2.line(FR, (0, H + 1), (FW, H + 1), (0, 0, 0), 2)
                        cv2.putText(FR, "Social distance detection", (210, H + 60),
                                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 0), 2)
                        cv2.rectangle(FR, (20, H + 80), (510, H + 180), (100, 100, 100), 2)
                        cv2.putText(FR, "Red Line Violations", (30, H + 100),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (100, 100, 0), 2)
                        cv2.putText(FR, "-- YELLOW: CLOSE", (50, H + 90 + 40),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 170, 170), 2)
                        cv2.putText(FR, "-- RED: VERY CLOSE", (50, H + 40 + 110),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

                        cv2.rectangle(FR, (535, H + 80), (1060, H + 140 + 40), (100, 100, 100), 2)
                        cv2.putText(FR, "DARK RED: HIGH RISK", (545, H + 100),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (100, 100, 0), 2)
                        cv2.putText(FR, "-- DARK RED: HIGH RISK", (565, H + 90 + 40),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 150), 2)
                        cv2.putText(FR, "-- ORANGE: LOW RISK", (565, H + 150),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 120, 255), 2)

                        cv2.putText(FR, "-- GREEN: SAFE", (565, H + 170),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 150, 0), 2)

                        tot_str = "TOTAL COUNT: " + str(total_p)
                        high_str = "HIGH RISK COUNT: " + str(high_risk_p)
                        low_str = "LOW RISK COUNT: " + str(low_risk_p)
                        safe_str = "SAFE COUNT: " + str(safe_p)

                        cv2.putText(FR, tot_str, (10, H + 25),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 0), 2)
                        cv2.putText(FR, safe_str, (200, H + 25),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 170, 0), 2)
                        cv2.putText(FR, low_str, (380, H + 25),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 120, 255), 2)
                        cv2.putText(FR, high_str, (630, H + 25),
                                    cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 0, 150), 2)

                        (x, y) = (boxes[i][0], boxes[i][1])
                        (w, h) = (boxes[i][2], boxes[i][3])
                        if status[kk] == 1:
                            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 150), 2)

                        elif status[kk] == 0:
                            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

                        else:
                            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 120, 255), 2)

                        kk += 1
                    for h in close_pair:
                        cv2.line(frame, tuple(h[0]), tuple(h[1]), (0, 0, 255), 2)
                        flag = 1
                    for b in s_close_pair:
                        cv2.line(frame, tuple(b[0]), tuple(b[1]), (0, 255, 255), 2)
                    FR[0:H, 0:W] = frame
                    frame = FR
                    if flag:
                        mutex = 1
                        cv2.imwrite("detectionFrame.jpg", frame)
                        cv2.waitKey(1)
            except Exception as e:
                print(e)



# def detection_video_frame():
#     time.sleep(0.5)
#     while True:
#         try:
#             flag = 0
#             (W, H) = (None, None)
#             frame = cv2.imread("detectionFrame.jpg")
#             if W is None or H is None:
#                 (H, W) = frame.shape[:2]
#                 FW = W
#                 if (W < 1075):
#                     FW = 1075
#                 FR = np.zeros((H + 210, FW, 3), np.uint8)
#
#                 col = (255, 255, 255)
#                 FH = H + 210
#             FR[:] = col
#
#             blob = cv2.dnn.blobFromImage(frame, 1 / 255.0, (416, 416),
#                                          swapRB=True, crop=False)
#             net.setInput(blob)
#             layerOutputs = net.forward(ln)
#
#             boxes = []
#             confidences = []
#             classIDs = []
#
#             for output in layerOutputs:
#
#                 for detection in output:
#
#                     scores = detection[5:]
#                     classID = np.argmax(scores)
#                     confidence = scores[classID]
#                     if LABELS[classID] == "person":
#
#                         if confidence > confid:
#                             box = detection[0:4] * np.array([W, H, W, H])
#                             (centerX, centerY, width, height) = box.astype("int")
#
#                             x = int(centerX - (width / 2))
#                             y = int(centerY - (height / 2))
#
#                             boxes.append([x, y, int(width), int(height)])
#                             confidences.append(float(confidence))
#                             classIDs.append(classID)
#
#             idxs = cv2.dnn.NMSBoxes(boxes, confidences, confid, thresh)
#
#             if len(idxs) > 0:
#                 status = []
#                 idf = idxs.flatten()
#                 close_pair = []
#                 s_close_pair = []
#                 center = []
#                 co_info = []
#
#                 for i in idf:
#                     (x, y) = (boxes[i][0], boxes[i][1])
#                     (w, h) = (boxes[i][2], boxes[i][3])
#                     cen = [int(x + w / 2), int(y + h / 2)]
#                     center.append(cen)
#                     cv2.circle(frame, tuple(cen), 1, (0, 0, 0), 1)
#                     co_info.append([w, h, cen])
#
#                     status.append(0)
#                 for i in range(len(center)):
#                     for j in range(len(center)):
#                         g = isclose(co_info[i], co_info[j])
#                         if g == 1:
#                             close_pair.append([center[i], center[j]])
#                             status[i] = 1
#                             status[j] = 1
#                         elif g == 2:
#                             s_close_pair.append([center[i], center[j]])
#                             if status[i] != 1:
#                                 status[i] = 2
#                             if status[j] != 1:
#                                 status[j] = 2
#                 kk = 0
#                 for i in idf:
#                     (x, y) = (boxes[i][0], boxes[i][1])
#                     (w, h) = (boxes[i][2], boxes[i][3])
#                     if status[kk] == 1:
#                         cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 150), 2)
#
#                     elif status[kk] == 0:
#                         cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
#
#                     else:
#                         cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 120, 255), 2)
#
#                     kk += 1
#                 for h in close_pair:
#                     cv2.line(frame, tuple(h[0]), tuple(h[1]), (0, 0, 255), 2)
#                     flag = 1
#                 for b in s_close_pair:
#                     cv2.line(frame, tuple(b[0]), tuple(b[1]), (0, 255, 255), 2)
#                 FR[0:H, 0:W] = frame
#                 frame = FR
#                 if flag:
#                     print('test')
#                     cv2.namedWindow("show_monitoring", cv2.WINDOW_NORMAL)
#                     cv2.resizeWindow("show_monitoring", 640, 480)
#                     cv2.imshow('show_monitoring', frame)
#                     cv2.waitKey(1)
#                     PlayRecording("./music/01.mp3")
#                     pygame.mixer.music.play()
#                     time.sleep(3)
#                     pygame.mixer.music.stop()
#
#         except Exception as e:
#             print(e)


# def video_show():
#     count = 0
#     time_start = time.time()
#     while True:
#         (grabbed, video_frame) = vs.read()
#         if not grabbed:
#             cv2.destroyWindow("show_monitoring")
#             break
#         cv2.namedWindow("show_monitoring", cv2.WINDOW_NORMAL)
#         cv2.resizeWindow("show_monitoring", 640, 480)
#         cv2.imshow('show_monitoring', video_frame)
#         cv2.waitKey(1)
#         if count == 30:
#             print('30帧')
#             cv2.imwrite("detectionFrame.jpg", video_frame)
#             count = 0
#             time_load = time.time()
#             print('loadTime:', time_load - time_start)
#             detection_frame_thread = multiprocessing.Process(target=detection_video_frame())
#             detection_frame_thread.start()
#         count += 1


def create_monitor():
    thread_video = ShowVideo()
    thread_video.start()
    detection_frame = DetectionFrame()
    detection_frame.start()


# 主函数
if __name__ == '__main__':
    create_monitor()
