//face_detect_from_video.cpp 定义控制台应用程序的入口点。
//从视频中识别人脸和人的眼睛
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <stdio.h>

using namespace std;
using namespace cv;

/* 检测人脸函数 */
void detectAndDisplay(Mat frame);

/** 人脸数据全局变量 */
String face_cascade_name, eyes_cascade_name;
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";

/* 主函数 */
int main(int argc, const char** argv)
{
	face_cascade_name = "./modle/haarcascade_frontalface_alt.xml";
	eyes_cascade_name = "./modle/haarcascade_eye.xml";
	VideoCapture capture;
	Mat frame;

	//-- 1. 加载人脸数据
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)没有识别到人脸\n"); return -1; };
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)没有识别到眼睛\n"); return -1; };

	//-- 2.打开系统
	capture.open(0); //打开摄像头
	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

	while (capture.read(frame)) //读取帧
	{
		if (frame.empty())
		{
			printf(" --(!) 没有读取到人脸，退出!");
			//break;
		}


		imshow("color", frame);
		//-- 3.加载分级器
		detectAndDisplay(frame);

		if (waitKey(10) == 'k') { break; } // escape
	}
	return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);  //BGR 转化为灰度图
	imshow("gray", frame_gray);
	equalizeHist(frame_gray, frame_gray);   //直方图均衡化

	//-- 寻找人脸
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, CASCADE_SCALE_IMAGE, Size(60, 60));

	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2); // 人脸中心坐标
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0); // 椭圆

		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;

		//寻找人脸眼睛
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 3, CASCADE_SCALE_IMAGE, Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2); //眼睛的中心
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25); //取整
			circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
		}
	}
	//-- Show what you got
	imshow(window_name, frame);
}
