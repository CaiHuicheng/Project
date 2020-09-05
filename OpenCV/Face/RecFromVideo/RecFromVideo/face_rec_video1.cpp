#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"
#include <stdio.h>
#include<iostream>

using namespace std;
using namespace cv;
using namespace cv::face;

/** Function Headers */
void detectAndDisplay(Mat frame);

/** Global variables */
String face_cascade_name = "./xml/haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;

String window_name = "Capture - Face Recognition";
string face1_path = ".\\images\\1.pgm";//1
string face2_path = ".\\images\\2.pgm";//2
string face3_path = ".\\images\\3.pgm";//3
string face4_path = ".\\images\\4.pgm";//��->4��

Ptr<EigenFaceRecognizer> modelPCA = EigenFaceRecognizer::create();// ����������ģ��  EigenFaceRecognizer

																  /** @function main */
int main(int argc, const char** argv)
{

	vector<Mat> images;
	images.push_back(imread(face1_path, CV_LOAD_IMAGE_GRAYSCALE));
	images.push_back(imread(face2_path, CV_LOAD_IMAGE_GRAYSCALE));
	images.push_back(imread(face3_path, CV_LOAD_IMAGE_GRAYSCALE));
	images.push_back(imread(face4_path, CV_LOAD_IMAGE_GRAYSCALE));

	vector<int> labels(4);
	for (int i = 1; i <= 4; i++)
		labels[i - 1] = i;

	//ѵ��
	modelPCA->train(images, labels);

	VideoCapture capture;
	Mat frame;

	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };

	//-- 2. Read the video stream
	capture.open(0); //������ͷ
	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

	while (capture.read(frame)) //��ȡ֡
	{
		if (frame.empty())
		{
			printf(" --(!) No captured frame -- Break!");
			break;
		}

		//-- 3. Apply the classifier to the frame
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
	equalizeHist(frame_gray, frame_gray);   //ֱ��ͼ���⻯
											//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(60, 60));

	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2); // ������������
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0); // ��Բ

		Mat faceROI = frame_gray(faces[i]);
		Mat face_test;
		// ������СΪ92*112  
		resize(faceROI, face_test, Size(92, 112));
		imwrite("lisa.pgm", face_test);
		double confidence;
		int predictPCA;
		modelPCA->predict(face_test, predictPCA, confidence);
		cout << "the predict result is " << predictPCA << endl << "confidence is " << confidence << endl;
		if (predictPCA == 4)
		{
			putText(frame, "Hello lisa", Point(faces[i].x, faces[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);

		}


	}
	//-- Show what you got
	imshow(window_name, frame);
}