//face_detect_from_video.cpp �������̨Ӧ�ó������ڵ㡣
//����Ƶ��ʶ���������˵��۾�
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <stdio.h>

using namespace std;
using namespace cv;

/* ����������� */
void detectAndDisplay(Mat frame);

/** ��������ȫ�ֱ��� */
String face_cascade_name, eyes_cascade_name;
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";

/* ������ */
int main(int argc, const char** argv)
{
	face_cascade_name = "./modle/haarcascade_frontalface_alt.xml";
	eyes_cascade_name = "./modle/haarcascade_eye.xml";
	VideoCapture capture;
	Mat frame;

	//-- 1. ������������
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)û��ʶ������\n"); return -1; };
	if (!eyes_cascade.load(eyes_cascade_name)) { printf("--(!)û��ʶ���۾�\n"); return -1; };

	//-- 2.��ϵͳ
	capture.open(0); //������ͷ
	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

	while (capture.read(frame)) //��ȡ֡
	{
		if (frame.empty())
		{
			printf(" --(!) û�ж�ȡ���������˳�!");
			//break;
		}


		imshow("color", frame);
		//-- 3.���طּ���
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

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);  //BGR ת��Ϊ�Ҷ�ͼ
	imshow("gray", frame_gray);
	equalizeHist(frame_gray, frame_gray);   //ֱ��ͼ���⻯

	//-- Ѱ������
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, CASCADE_SCALE_IMAGE, Size(60, 60));

	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2); // ������������
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0); // ��Բ

		Mat faceROI = frame_gray(faces[i]);
		std::vector<Rect> eyes;

		//Ѱ�������۾�
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 3, CASCADE_SCALE_IMAGE, Size(30, 30));

		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2); //�۾�������
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25); //ȡ��
			circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
		}
	}
	//-- Show what you got
	imshow(window_name, frame);
}
