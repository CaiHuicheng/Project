#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"
#include <stdio.h>
#include<iostream>

using namespace std;
using namespace cv;
using namespace cv::face;

/** Function Headers */
void detectAndDisplay(Mat frame);
static  void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, int max, int min, char separator);

/** Global variables */
String face_cascade_name = "./xml/haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;
Ptr<EigenFaceRecognizer> modelPCA = EigenFaceRecognizer::create();// ����������ģ��  EigenFaceRecognizer

String window_name = "Capture - Face Recognition";

/** @function main */
int main(int argc, const char** argv)
{
	string csvFile = "face.txt";
	vector<Mat> images;
	vector<int> labels;
	int CountMax = 9, CountMin = 0;

	// ��ȡcsv�ļ�  
	try
	{
		read_csv(csvFile, images, labels, CountMax, CountMin, ';'); //��ȡcsvFile�����е�img��label  
	}
	catch (cv::Exception& e) // �쳣���  
	{
		cerr << "Error opening file\" " << csvFile << "\".reason: " << e.msg << endl;
		exit(-1);
	}


	// ��δ��ȡ���㹻ͼƬ��Ҳ�˳�  
	if (images.size() <= 1)
	{
		string errMsg = "THis demo needs at least 2 images to work.please add images!";
		CV_Error(CV_StsError, errMsg);

	}
	cout << "train1.��ȡok" << endl;

	// ѵ��ģ�ͣ�����ѵ���õ�����ģ�ͱ��浽.xml��   
	modelPCA->train(images, labels); //ѵ��  
	modelPCA->save("MyFacePcaModel.xml");
	cout << "train2.������ģ��ok" << endl;

	// ��Ƶ�ɼ�
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

		resize(faceROI, face_test, Size(92, 112)); // ������СΪ92*112 
		double confidence;
		int predictPCA;

		modelPCA->read("MyFacePcaModel.xml");//����ģ��
		modelPCA->predict(face_test, predictPCA, confidence);
		cout << "the predict result is " << predictPCA << endl << "confidence is " << confidence << endl;
		if (predictPCA == 40)
		{
			putText(frame, "Hello Cai", Point(faces[i].x, faces[i].y), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 255), 2);
		}
	}
	imshow(window_name, frame);
}


static  void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, int max, int min, char separator)
{
	std::ifstream  file(filename.c_str(), ifstream::in); // ��inģʽ����ȡ�ļ�ģʽ�����ļ� ,ʵ���ǽ�filename�ļ������� ��file 

	if (!file)
	{
		string error_message = "No valid input file was given,please check the given filename";
		CV_Error(CV_StsBadArg, error_message);

	}
	int ii = 0;

	/**********************��ȡ�ļ�.txt����****************************/
	string line, path, label;
	// [1]��ȡfile�ļ��е�һ���ַ����� line  
	while (getline(file, line, '\n'))  // ���ƣ�ֱ������file�ļ�ĩβ��eof��ʶ����������while  
	{
		// [2]��line�����ַ�����ȡ��lines(��)��  
		stringstream lines(line); //����->lines��������ȡ�ַ�ʱ��ָ���������������line��string���̶��ģ������еĶ�ȡÿ�ζ��Ǵ�lineͷ��ʼ  
								  // [3]��ȡ�ļ��е�·���ͱ�ǩ  
		getline(lines, path, separator); //��ʱ������ߵ�path֮���λ�ã������ֺŴ���  
		getline(lines, label);
		// [4]��ͼƬ�ͱ�ǩ����imgs �� labels  
		if ((path.empty() == 0) && (label.empty() == 0))
		{
			if (ii % 10 <= max && ii % 10 >= min)  //Ĭ��ÿ�����10����Ƭ  
			{
				Mat img = imread(path, 0);  //�ڶ�������Ϊ0 !!!  
											//Mat img = imread(ImageFileAddress, CV_LOAD_IMAGE_GRAYSCALE)��CV_LOAD_IMAGE_GRAYSCALEֵΪ 0��ָ��ͼ��ԭ��Ϊ��CV_LOAD_IMAGE_UNCHANGED����  
				if (img.data != 0)
				{
					images.push_back(img); // ��ͼƬ ��ӵ�images��  
					labels.push_back(atoi(label.c_str()));
				}
			}
			if (ii < 9) ii++;
			else ii = 0;

		}
	}
}