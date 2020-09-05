#include "base.h"
#include <opencv2/core/eigen.hpp>//for cv::cv2eigen

int main(int argc,char** argv)
{
	CAMERA_INTRINSIC_PARAMETERS C;
	C.scale=1000;
	C.cx=325.5;
	C.cy=253.5;
	C.fx=518.0;
	C.fy=519.0;
	FRAME frame1,frame2;
	frame1.rgb = cv::imread("color_3.png");
	frame1.depth = cv::imread("depth_3.png", -1);
	frame2.rgb = cv::imread("color_4.png");
	frame2.depth = cv::imread("depth_4.png", -1);
	
	//求解相机运动
	computeDetectorAndDescriptor(frame1);
	computeDetectorAndDescriptor(frame2);
	cv::Mat rvec,tvec,inliers;
	estimateMotion(frame1,frame2,C,rvec,tvec,inliers);

	//分别产生两幅图像对应的点云
	PointCloud::Ptr cloud1(new PointCloud);
	PointCloud::Ptr cloud2(new PointCloud);
	generatePointCloud(cloud1,frame1,C);
	generatePointCloud(cloud2,frame2,C);

	Eigen::Isometry3d T=rtvec2Isometry3d(rvec,tvec);
	//点云转换与拼接
	PointCloud::Ptr output(new PointCloud);
	pcl::transformPointCloud(*cloud1,*output,T.matrix());
	*cloud2+=*output;
	
	for(size_t i=0;i<cloud2->points.size();i++)
	{
		cloud2->points[i].y=-cloud2->points[i].y;
		cloud2->points[i].z=-cloud2->points[i].z;
	}
	pcl::io::savePCDFile("/data/result.pcd",*cloud2);
	cout<<"Final result saved."<<endl;
	
	pcl::visualization::CloudViewer viewer("viewer");
	viewer.showCloud(cloud2);
	while(!viewer.wasStopped())
	{

	}
	return 0;
}
