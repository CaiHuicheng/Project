import cv2
import os
if True:
    pathLoad = os.getcwd()+"/image/load.jpg"
    print(pathLoad)
    ref, frame = cv2.imread(pathLoad)
    cv2.imshow("1", frame)
cv2.destroyAllWindows()