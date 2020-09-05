import cv2

cap = cv2.VideoCapture("vid_short.mp4")
i = 0

while True:
    (grabbed, frame) = cap.read()
    cv2.imshow("test", frame)
    cv2.waitKey(1)
    if not grabbed:
        exit(0)
    name = "c1s1_" + str(i) + ".jpg"
    cv2.imwrite(name,frame)
    i += 1

