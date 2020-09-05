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
Ptr<EigenFaceRecognizer> modelPCA = EigenFaceRecognizer::create();// 创建特征脸模型  EigenFaceRecognizer

String window_name = "Capture - Face Recognition";

/** @function main */
int main(int argc, const char** argv)
{
	string csvFile = "face.txt";
	vector<Mat> images;
	vector<int> labels;
	int CountMax = 9, CountMin = 0;

	// 读取csv文件  
	try
	{
		read_csv(csvFile, images, labels, CountMax, CountMin, ';'); //读取csvFile中所有的img和label  
	}
	catch (cv::Exception& e) // 异常检查  
	{
		cerr << "Error opening file\" " << csvFile << "\".reason: " << e.msg << endl;
		exit(-1);
	}


	// 若未读取到足够图片，也退出  
	if (images.size() <= 1)
	{
		string errMsg = "THis demo needs at least 2 images to work.please add images!";
		CV_Error(CV_StsError, errMsg);

	}
	cout << "train1.读取ok" << endl;

	// 训练模型，并将训练好的人脸模型保存到.xml中   
	modelPCA->train(images, labels); //训练  
	modelPCA->save("MyFacePcaModel.xml");
	cout << "train2.创建脸模型ok" << endl;

	// 视频采集
	VideoCapture capture;
	Mat frame;

	//-- 1. Load the cascades
	if (!face_cascade.load(face_cascade_name)) { printf("--(!)Error loading face cascade\n"); return -1; };

	//-- 2. Read the video stream
	capture.open(0); //打开摄像头
	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

	while (capture.read(frame)) //读取帧
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

	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);  //BGR 转化为灰度图
	equalizeHist(frame_gray, frame_gray);   //直方图均衡化
	//-- Detect faces
	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(60, 60));

	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2); // 人脸中心坐标
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0); // 椭圆

		Mat faceROI = frame_gray(faces[i]);
		Mat face_test;

		resize(faceROI, face_test, Size(92, 112)); // 调整大小为92*112 
		double confidence;
		int predictPCA;

		modelPCA->read("MyFacePcaModel.xml");//加载模型
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
	std::ifstream  file(filename.c_str(), ifstream::in); // 以in模式（读取文件模式）打开文件 ,实际是将filename文件关联给 流file 

	if (!file)
	{
		string error_message = "No valid input file was given,please check the given filename";
		CV_Error(CV_StsBadArg, error_message);

	}
	int ii = 0;

	/**********************读取文件.txt内容****************************/
	string line, path, label;
	// [1]读取file文件中的一行字符串给 line  
	while (getline(file, line, '\n'))  // 控制：直到读到file文件末尾（eof标识），才跳出while  
	{
		// [2]将line整行字符串读取到lines(流)中  
		stringstream lines(line); //区别->lines是流，读取字符时，指针会随流而动；而line是string，固定的，下文中的读取每次都是从line头开始  
								  // [3]读取文件中的路径和标签  
		getline(lines, path, separator); //此时光标已走到path之后的位置（即；分号处）  
		getline(lines, label);
		// [4]将图片和标签加入imgs 和 labels  
		if ((path.empty() == 0) && (label.empty() == 0))
		{
			if (ii % 10 <= max && ii % 10 >= min)  //默认每个类别共10张照片  
			{
				Mat img = imread(path, 0);  //第二个参数为0 !!!  
											//Mat img = imread(ImageFileAddress, CV_LOAD_IMAGE_GRAYSCALE)，CV_LOAD_IMAGE_GRAYSCALE值为 0，指灰图（原本为“CV_LOAD_IMAGE_UNCHANGED”）  
				if (img.data != 0)
				{
					images.push_back(img); // 将图片 添加到images中  
					labels.push_back(atoi(label.c_str()));
				}
			}
			if (ii < 9) ii++;
			else ii = 0;

		}
	}
}