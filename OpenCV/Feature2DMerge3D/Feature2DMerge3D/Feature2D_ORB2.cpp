#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc_c.h> 
#include <opencv2/imgproc/imgproc.hpp>  
#include <string>
#include <vector>
#include <iostream>
using namespace cv;
using namespace std;


unsigned int hamdist(unsigned int x, unsigned int y)
{
	unsigned int dist = 0, val = x ^ y;
	// Count the number of set bits 
	while (val)
	{
		++dist;
		val &= val - 1;
	}
	return dist;
}

unsigned int hamdist2(unsigned char* a, unsigned char* b, size_t size)
{
	HammingLUT lut;
	unsigned int result;
	result = lut((a), (b), size);
	return result;
}

void naive_nn_search(vector<KeyPoint>& keys1, Mat& descp1, vector<KeyPoint>& keys2, Mat& descp2, vector<DMatch>& matches)
{
	for (int i = 0; i < (int)keys2.size(); i++)
	{
		unsigned int min_dist = INT_MAX;
		int min_idx = -1;
		//注意指针的用法:Mat.ptr(i)
		unsigned char* query_feat = descp2.ptr(i);
		for (int j = 0; j < (int)keys1.size(); j++)
		{
			unsigned char* train_feat = descp1.ptr(j);
			unsigned int dist = hamdist2(query_feat, train_feat, 32);
			if (dist < min_dist)
			{
				min_dist = dist;
				min_idx = j;
			}
		}
		//if(min_dist <= (unsigned int)(second_dist * 0.8){ 
		if (min_dist <= 50)
		{
			matches.push_back(DMatch(i, min_idx, 0, (float)min_dist));
		}
	}
}

void naive_nn_search2(vector<KeyPoint>& keys1, Mat& descp1, vector<KeyPoint>& keys2, Mat& descp2, vector<DMatch>& matches)
{
	for (int i = 0; i < (int)keys2.size(); i++)
	{
		unsigned int min_dist = INT_MAX;
		unsigned int sec_dist = INT_MAX;
		int min_idx = -1, sec_idx = -1;
		unsigned char* query_feat = descp2.ptr(i);
		for (int j = 0; j < (int)keys1.size(); j++)
		{
			unsigned char* train_feat = descp1.ptr(j);
			unsigned int dist = hamdist2(query_feat, train_feat, 32);
			//最短距离
			if (dist < min_dist)
			{
				sec_dist = min_dist;
				sec_idx = min_idx;
				min_dist = dist;
				min_idx = j;
			}
			//次短距离
			else if (dist < sec_dist)
			{
				sec_dist = dist; sec_idx = j;
			}
		}
		if (min_dist <= (unsigned int)(sec_dist * 0.8) && min_dist <= 50)
		{
			matches.push_back(DMatch(i, min_idx, 0, (float)min_dist));
		}
	}
}

int main(int argc, char* argv[])
{
	//读取要匹配的两张图像
	Mat img_color1 = imread("color_1.png");//图片路径与.cpp文件放一起，或者绝对路径
	Mat img_color2 = imread("color_2.png");//图片路径与.cpp文件放一起，或者绝对路径
	Mat img_1;
	Mat img_2;
	//GaussianBlur(img1, img1, Size(5, 5), 0); 
	//GaussianBlur(img2, img2, Size(5, 5), 0);   
	Ptr<ORB> orb1 = (100, ORB::CommonParams(1.2, 1));
	Ptr<ORB> orb2 = (10, ORB::CommonParams(1.2, 1));
	vector<KeyPoint> keys1, keys2;
	Mat descriptors1, descriptors2;
	int64 st, et;

	//提取ORB特征;
	orb1(img_1, Mat(), keys1, descriptors1, false);
	printf("tem feat num: %d\n", keys1.size());
	st = cvGetTickCount();
	orb2(img_2, Mat(), keys2, descriptors2, false);
	et = cvGetTickCount();
	printf("orb2 extraction time: %f\n", (et - st) / (double)cvGetTickFrequency() / 1000.);
	printf("query feat num: %d\n", keys2.size());

	// find matches 
	vector<DMatch> matches;
	st = cvGetTickCount();
	for (int i = 0; i < 10; i++)
	{
		naive_nn_search2(keys1, descriptors1, keys2, descriptors2, matches);
	}
	et = cvGetTickCount();
	printf("match time: %f\n", (et - st) / (double)cvGetTickFrequency() / 1000.);
	printf("matchs num: %d\n", matches.size());

	Mat showImg;
	drawMatches(img_2, keys2, img_1, keys1, matches, showImg, CV_RGB(0, 255, 0), CV_RGB(0, 0, 255));
	string winName = "Matches";
	namedWindow(winName, WINDOW_AUTOSIZE);
	imshow(winName, showImg);
	waitKey(0);   vector<Point2f> pt1; vector<Point2f> pt2;

	for (int i = 0; i < (int)matches.size(); i++)
	{
		pt1.push_back(Point2f(keys2[matches[i].queryIdx].pt.x, keys2[matches[i].queryIdx].pt.y));
		pt2.push_back(Point2f(keys1[matches[i].trainIdx].pt.x, keys1[matches[i].trainIdx].pt.y));
	}

	Mat homo, homo1;
	st = cvGetTickCount(); //寻找两个矩阵的透视变换3*3矩阵☆☆☆☆☆☆☆☆☆☆☆☆;
	homo1 = findHomography(pt1, pt2, CV_RANSAC, (5.0));
	homo1.convertTo(homo, CV_32F);
	//normalize(homo,homo,1,0); printf("homo\n"
	"%f %f %f\n"
		"%f %f %f\n"
		"%f %f %f\n",
		homo.at<float>(0, 0), homo.at<float>(0, 1), homo.at<float>(0, 2),
		homo.at<float>(1, 0), homo.at<float>(1, 1), homo.at<float>(1, 2),
		homo.at<float>(2, 0), homo.at<float>(2, 1), homo.at<float>(2, 2));
		//目标图像顶点坐标☆☆☆☆☆☆☆☆☆☆☆☆
		CvPoint src_corners[4] = { {0,0}, {img_2.cols,0}, {img_2.cols, img_2.rows}, {0, img_2.rows} };
		CvPoint dst_corners[4];
		double h[9];
		h[0] = homo.at<float>(0, 0);
		h[1] = homo.at<float>(0, 1);
		h[2] = homo.at<float>(0, 2);
		h[3] = homo.at<float>(1, 0);
		h[4] = homo.at<float>(1, 1);
		h[5] = homo.at<float>(1, 2);
		h[6] = homo.at<float>(2, 0);
		h[7] = homo.at<float>(2, 1);
		h[8] = homo.at<float>(2, 2);
		size_t i;
		//利用提取到的3*3透视变换矩阵，对目标图像的四个顶点的坐标进行透视变换
		for (i = 0; i < 4; i++)
		{
			double x = src_corners[i].x, y = src_corners[i].y;
			double Z = 1. / (h[6] * x + h[7] * y + h[8]);
			double X = (h[0] * x + h[1] * y + h[2])*Z;
			double Y = (h[3] * x + h[4] * y + h[5])*Z;
			dst_corners[i] = cvPoint(cvRound(X), cvRound(Y));
		}
		Mat img = imread(image_filename1, 1);
		//把变换后的坐标用直线连接，定位！
		for (i = 0; i < 4; i++)
		{
			CvPoint r1 = dst_corners[i % 4];
			CvPoint r2 = dst_corners[(i + 1) % 4];
			line(img, cvPoint(r1.x, r1.y),
				cvPoint(r2.x, r2.y), Scalar(0, 0, 255), 2);
		}
		imshow("location", img);
		et = cvGetTickCount();
		printf("ransac time: %fms\n", (et - st) / (double)cvGetTickFrequency() / 1000.);
		waitKey(0);
		vector<Point2f> reproj;
		reproj.resize(pt1.size());
		//向量数组的透视变换;☆☆☆☆☆☆☆☆☆☆☆☆
		perspectiveTransform(pt1, reproj, homo);
		Mat diff;
		diff = Mat(reproj) - Mat(pt2);
		int inlier = 0;
		double err_sum = 0;
		for (int i = 0; i < diff.rows; i++)
		{
			uchar* ptr = diff.ptr(i);
			float err = ptr[0] * ptr[0] + ptr[1] * ptr[1];
			if (err < 25.f)
			{
				inlier++; err_sum += sqrt(err);
			}
		}
		printf("inlier num: %d\n", inlier);
		printf("ratio %f\n", inlier / (float)(diff.rows));
		printf("mean reprojection error: %f\n", err_sum / inlier);
		return 0;
}