
/**
* 概述: 使用FAST进行特征点检测
* 类和函数: FAST函数，FastFeatureDetector类
*/
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/features2d/features2d.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img_color = imread("feature.png");//图片路径与.cpp文件放一起，或者绝对路径
	Mat img;
	if (img_color.empty()) {
		printf("图片加载失败！！！");
	}
	imshow("color", img_color);
	cvtColor(img_color, img, CV_BGR2GRAY);
	imshow("Grey", img);

	vector<KeyPoint> keypoints;
	Ptr<FastFeatureDetector> fast = FastFeatureDetector::create(20);
	fast->detect(img, keypoints);

	//-- 绘制特征点
	Mat img_keypoints;
	drawKeypoints(img, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//-- 显示特征点
	imshow("Keypoints", img_keypoints);
	imwrite("fast_detection_result.png", img_keypoints);

	waitKey(0);
	return 0;
}