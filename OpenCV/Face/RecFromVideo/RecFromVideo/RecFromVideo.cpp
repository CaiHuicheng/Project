#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"
#include <stdio.h>
#include<iostream>

using namespace std;
using namespace cv;
using namespace cv::face;

// �������
void detectAndDisplay(Mat frame);

//ȫ�ֱ���
String face_cascade_name = "D:\\Face\\RecFromVideo\\RecFromVideo\\modle\\haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;
String window_name = "Capture - Face Recognition";
string face1_path = "./image/1.pgm";//1
string face2_path = "./image/2.pgm";//2
string face3_path = "./image/3.pgm";//3
string face4_path = "./image/4.pgm";//��->4��
//string face4_path = "4.png";//��->4��

Ptr<EigenFaceRecognizer> modelPCA = EigenFaceRecognizer::create();// ����������ģ��  EigenFaceRecognizer


int main(int argc, const char** argv)
{

	vector<Mat> images;
	//Mat test;
	//test = imread(face4_path, CV_LOAD_IMAGE_GRAYSCALE);
	//imshow("ԭͼ", test);
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

	//��������������
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };

	//��ȡ����ͷ���� ÿһ֡
	capture.open(0); //������ͷ
	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

	while (capture.read(frame)) //��ȡ֡
	{
		if (frame.empty())
		{
			printf(" --(!) No captured frame -- Break!");
			break;
		}

		//���ط�����
		detectAndDisplay(frame);

		if (waitKey(10) == 'k') { break; } // escape  
	}
	system("pause");
	return 0;
}

//�����⺯��
void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);  //BGR ת��Ϊ�Ҷ�ͼ
	equalizeHist(frame_gray, frame_gray);   //ֱ��ͼ���⻯
	//detectMultiScale ��⺯�� ���Կ��ٷ��ĵ�
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
			putText(frame, "Hello Cai", Point(faces[i].x, faces[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);

		}


	}
	//��ʾ���
	imshow(window_name, frame);
}