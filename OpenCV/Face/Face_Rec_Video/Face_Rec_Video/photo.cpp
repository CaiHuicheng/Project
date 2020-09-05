#include <opencv2/core/core.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/opencv.hpp>  

#include <vector>  
#include <cstdio>  

using namespace std;
using namespace cv;

int main()
{

	//加载分类器  
	CascadeClassifier cascade;
	bool test = cascade.load("D:\\Face\\FacePhoto\\FacePhoto\\modle\\haarcascade_frontalface_alt2.xml");
	//bool test = cascade.load("haarcascade_frontalface_alt2.xml");
	cout << test << endl; //相对地址加载时发现加载不进去 test = 0；
	Mat srcImage, grayImage, dstImage;
	//读取图片  
	srcImage = imread("001.jpg");
	dstImage = srcImage.clone();
	imshow("原图", srcImage);

	grayImage.create(srcImage.size(), srcImage.type());
	cvtColor(srcImage, grayImage, CV_BGR2GRAY); // 生成灰度图，提高检测效率  

	// 定义7种颜色，用于标记人脸  
	Scalar colors[] =
	{
		// 红橙黄绿青蓝紫  
		CV_RGB(255, 0, 0),
		CV_RGB(255, 97, 0),
		CV_RGB(255, 255, 0),
		CV_RGB(0, 255, 0),
		CV_RGB(0, 255, 255),
		CV_RGB(0, 0, 255),
		CV_RGB(160, 32, 240)
	};

	//检测人脸  
	vector<Rect> rect;
	cascade.detectMultiScale(grayImage, rect, 1.1, 2, 0);  // 分类器对象调用  
	/*cascade.detectMultiScale(grayImage, rect,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		| CV_HAAR_SCALE_IMAGE
		, Size(30, 30));
		*/
	printf("检测到人脸个数：%d\n", rect.size());

	//标记--在脸部画圆  
	for (int i = 0; i < rect.size(); i++)
	{
		Point  center;
		int radius;
		center.x = cvRound((rect[i].x + rect[i].width * 0.5));
		center.y = cvRound((rect[i].y + rect[i].height * 0.5));

		radius = cvRound((rect[i].width + rect[i].height) * 0.25);
		circle(dstImage, center, radius, colors[i % 7], 2);
	}

	//显示  
	imshow("人脸识别detectMultiScale", dstImage);

	waitKey(0);
	return 0;
}