#include <iostream>
 
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/nonfree.hpp>             //  sift特征在这个头文件中  
 
#include <vector>
 
#pragma comment(lib,"opencv_core2410d.lib")              
#pragma comment(lib,"opencv_highgui2410d.lib")              
#pragma comment(lib,"opencv_imgproc2410d.lib") 
#pragma comment(lib,"opencv_features2d2410d.lib") 
#pragma comment(lib,"opencv_nonfree2410d.lib") 
 
using namespace std;
using namespace cv;
 
//struct DrawMatchesFlags
//{   
//	enum    {
//		DEFAULT = 0, // 输出图像将被创建(Mat::create),
//		// 只画出特征点，而不画出周围的circle包含特征点的大小和方向.
//		DRAW_OVER_OUTIMG = 1, // 输出图像将被创建(using Mat::create)，匹配点将被画在输出图像的内容上.
//		NOT_DRAW_SINGLE_POINTS = 2, // 单个的点不画出.
//		DRAW_RICH_KEYPOINTS = 4 // 对每个特征点周围的circle，包含特征点的大小和方向将被画出.    
//	};
//};
void fast_feature()
{
	Mat image;
	image = imread("swan.jpg");
	// vector of keyPoints
	std::vector<KeyPoint> keyPoints;
	// construction of the fast feature detector object
	FastFeatureDetector fast(80);	// 检测的阈值为80
	// feature point detection
	fast.detect(image,keyPoints);
	drawKeypoints(image, keyPoints, image, Scalar::all(-1), DrawMatchesFlags::DRAW_OVER_OUTIMG);
	imshow("FAST feature", image);
	//cvWaitKey(0);
}
 
 
 
bool sift_feature()
{
	Mat image = imread("swan.jpg", 1);
	if(!image.data)
	{
		cout << "Fail to load image" << endl;
		return 0;
		
	}
	vector<KeyPoint> keypoints;          //  存放关键点
 
	// 其中0.03代表特征的阀值：用于去除低对比度的关键点   10是用于降低直线敏感度的阀值：去除不稳点的边缘响应点
	SiftFeatureDetector sift(0.03, 10.0);   
	sift.detect(image, keypoints);
 
	drawKeypoints(image, keypoints, image, Scalar(255,255,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	namedWindow("sift");
	imshow("sift", image);
	
	
}
 
void main()
{
	sift_feature();
	fast_feature();
 
	waitKey(0);
	
}