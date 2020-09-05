#include<iostream>
#include<vector>
using namespace std;

//Eigen
#include<Eigen/Core>
#include<Eigen/Geometry>
//openCV
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/eigen.hpp>
//pcl
#include <pcl/common/transforms.h>
#include <pcl/visualization/cloud_viewer.h>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>

//pcl 点云类型
typedef pcl::PointXYZRGBA Point3D;
typedef pcl::PointCloud<Point3D> PointCloud;
//定义像素坐标转相机坐标的S
const double S = 875;//5000 1000 875 
//相机内参 874.85, 0, 637.32, 0, 874.85, 372.90, 0, 0, 1 => fx 0 cx 0 fy cy 0 0 1
const double cx = 637.32;
const double fx = 874.85;
const double fy = 874.85;
const double cy = 372.90;

struct FRAME
{
	cv::Mat rgb, depth;
	vector<cv::KeyPoint> kp;
	cv::Mat desp;
};
//point2dTo3d
cv::Point3f point2dTo3d(cv::Point3f& point);

//计算特征点
void computeDetectorAndDescriptor(FRAME& f);

//相机RT
int estimateMotion(FRAME& frame1, FRAME& frame2, cv::Mat& rvec, cv::Mat& tvec, cv::Mat& inliers);

//RGB和depth生成云点
void generatePointCloud(PointCloud::Ptr& cloud, FRAME& f);

//把旋转矩阵和旋转向量转换成为SE(3)
Eigen::Isometry3d rtvec2Isometry3d(cv::Mat& rvec, cv::Mat& tvec);
//拼接点云
//把cloud1通过R和T转换成cloud2坐标系下的点云与cloud2相加
PointCloud::Ptr jointPointCloud(PointCloud::Ptr& cloud1, FRAME& frame, cv::Mat& rvec, cv::Mat& tvec);

int main(int argc,char** argv)
{
	//读取文件
	FRAME frame1, frame2;
	frame1.rgb = cv::imread("color_0.png");
	frame1.depth = cv::imread("depth_0.png", -1);
	frame2.rgb = cv::imread("color_3.png");
	frame2.depth = cv::imread("depth_3.png", -1);
	//frame1.rgb = cv::imread("1.png");
	//frame1.depth = cv::imread("1_depth.png", -1);
	//frame2.rgb = cv::imread("2.png");
	//frame2.depth = cv::imread("2_depth.png", -1);

	//特征点提取
	computeDetectorAndDescriptor(frame1);
	computeDetectorAndDescriptor(frame2);
	cv::Mat r, t, inliers;
	estimateMotion(frame1, frame2, r, t, inliers);

	//生成云点
	PointCloud::Ptr cloud1(new PointCloud);
	PointCloud::Ptr cloud2(new PointCloud);
	generatePointCloud(cloud1, frame1);
	generatePointCloud(cloud2, frame2);

	Eigen::Isometry3d T = rtvec2Isometry3d(r, t);
	//拼接云点
	PointCloud::Ptr output(new PointCloud);
	pcl::transformPointCloud(*cloud1, *output, T.matrix());
	*cloud2 += *output;

	for (size_t i = 0; i<cloud2->points.size(); i++)
	{
		cloud2->points[i].y = -cloud2->points[i].y;
		cloud2->points[i].z = -cloud2->points[i].z;
	}
	pcl::io::savePCDFile("/data/result.pcd", *cloud2);
	cout << "Final result saved." << endl;

	pcl::visualization::CloudViewer viewer("viewer");
	viewer.showCloud(cloud2);
	while (!viewer.wasStopped())
	{

	}
	return 0;
}


cv::Point3f point2dTo3d(cv::Point3f& point)
{
	cv::Point3f p; // 3D点
	p.z = double(point.z) / S;
	p.x = (point.x - cx) * p.z /fx;
	p.y = (point.y - cy) * p.z /fy;
	return p;
}


void computeDetectorAndDescriptor(FRAME& f)
{
	cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();;
	cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();

	detector->detect(f.rgb, f.kp);
	descriptor->compute(f.rgb, f.kp, f.desp);

	return;
}


int estimateMotion(FRAME& frame1, FRAME& frame2, cv::Mat& rvec, cv::Mat& tvec, cv::Mat& inliers)
{
	vector<cv::DMatch> matches;
	cv::BFMatcher matcher;
	matcher.match(frame1.desp, frame2.desp, matches);
	cout << "Find total " << matches.size() << "matches." << endl;
	vector<cv::DMatch> goodMatches;
	double minDis = 9999;
	for (size_t i = 0; i<matches.size(); i++)
	{
		if (matches[i].distance<minDis)
			minDis = matches[i].distance;
	}
	cout << "min dis = " << minDis << endl;

	for (size_t i = 0; i<matches.size(); i++)
	{
		if (matches[i].distance<10 * minDis)
			goodMatches.push_back(matches[i]);
	}

	vector<cv::Point3f> pts_obj;
	vector<cv::Point2f> pts_img;

	for (size_t i = 0; i<goodMatches.size(); i++)
	{
		cv::Point2f p = frame1.kp[goodMatches[i].queryIdx].pt;
		ushort d = frame1.depth.ptr<ushort>(int(p.y))[int(p.x)];
		if (d == 0)
			continue;
		pts_img.push_back(cv::Point2f(frame2.kp[goodMatches[i].trainIdx].pt));

		//u,v,d --》 x,y,z
		cv::Point3f pt(p.x, p.y, d);
		cv::Point3f pd = point2dTo3d(pt);
		pts_obj.push_back(pd);
	}
	cout << "inliers: " << pts_obj.size() << endl;
	if (pts_obj.size()<5)
	{
		cout << " no enourh inliers!" << endl;
		return 0;
	}
	double camera_matrix_data[3][3] = {
		{ fx,0,cx },
		{ 0,fy,cy },
		{ 0,0,1 }
	};
	//相机矩阵
	cv::Mat cameraMatrix(3, 3, CV_64F, camera_matrix_data);
	//求解pnp
	cv::solvePnPRansac(pts_obj, pts_img, cameraMatrix, cv::Mat(), rvec, tvec, false, 100, 1.0, 0.99, inliers);
	cout << "R=" << rvec << endl;
	cout << "t=" << tvec << endl;
	return 1;
}


void generatePointCloud(PointCloud::Ptr& cloud, FRAME& f)
{
	for (int m = 0; m<f.depth.rows; m++)
		for (int n = 0; n<f.depth.cols; n++)
		{
			ushort d = f.depth.ptr<ushort>(m)[n];
			//排除 bad 点
			if (d == 0)
				continue;
			Point3D p;

			//计算点云相机坐标
			p.z = double(d) / S;
			p.x = (n - cx)*p.z /fx;
			p.y = (m - cy)*p.z /fy;

			p.b = f.rgb.ptr<uchar>(m)[n * 3];
			p.g = f.rgb.ptr<uchar>(m)[n * 3 + 1];
			p.r = f.rgb.ptr<uchar>(m)[n * 3 + 2];

			cloud->points.push_back(p);
		}
	//保存点云
	cloud->height = 1;
	cloud->width = cloud->points.size();
	cout << "point cloud size=" << cloud->points.size() << endl;
	cloud->is_dense = false;
	return;
}

Eigen::Isometry3d rtvec2Isometry3d(cv::Mat& rvec, cv::Mat& tvec)
{
	//旋转矩阵	
	cv::Mat R;
	cv::Rodrigues(rvec, R);
	Eigen::Matrix3d rev;
	cv::cv2eigen(R, rev);

	// 由旋转向量r和平移向量t得到SE（3）T
		//T是SE(3)特殊欧式群里的元素
	Eigen::Isometry3d T = Eigen::Isometry3d::Identity();

	Eigen::AngleAxisd angle(rev);
	T = angle;
	T(0, 3) = tvec.at<double>(0, 0);
	T(1, 3) = tvec.at<double>(0, 1);
	T(2, 3) = tvec.at<double>(0, 2);
	return T;
}

PointCloud::Ptr jointPointCloud(PointCloud::Ptr& cloud1, FRAME& frame, cv::Mat& rvec, cv::Mat& tvec)
{

	PointCloud::Ptr cloud2(new PointCloud());
	generatePointCloud(cloud2, frame);
	//旋转矩阵
	cv::Mat R;
	cv::Rodrigues(rvec, R);
	Eigen::Matrix3d rev;
	cv::cv2eigen(R, rev);

	Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
	Eigen::AngleAxisd angle(rev);
	T = angle;
	T(0, 3) = tvec.at<double>(0, 0);
	T(1, 3) = tvec.at<double>(0, 1);
	T(2, 3) = tvec.at<double>(0, 2);
	cout << "T= " << T.matrix() << endl;

	//点云转换与拼接
	PointCloud::Ptr output_(new PointCloud);
	pcl::transformPointCloud(*cloud1, *output_, T.matrix());
	*cloud2 += *output_;

	//Voxel grid 滤波降采样
	static pcl::VoxelGrid<Point3D> voxel;
	double gridsize = 0.01;
	voxel.setLeafSize(gridsize, gridsize, gridsize);
	voxel.setInputCloud(cloud2);
	PointCloud::Ptr tmp(new PointCloud());
	voxel.filter(*tmp);
	return tmp;
}