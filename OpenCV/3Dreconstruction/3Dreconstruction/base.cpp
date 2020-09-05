#include "base.h"
#include <opencv2/core/eigen.hpp>//for cv::cv2eigen

//point2dT03d 将单个点从图像转换成为空间坐标
//input:3维点Point3f(u,v,d)
cv::Point3f point2dTo3d(cv::Point3f& point,CAMERA_INTRINSIC_PARAMETERS& camera)
{
	cv::Point3f p; // 3D 点
    p.z = double( point.z ) / camera.scale;
    p.x = ( point.x - camera.cx) * p.z / camera.fx;
    p.y = ( point.y - camera.cy) * p.z / camera.fy;
    return p;
}

//计算关键点和描述子
void computeDetectorAndDescriptor(FRAME& f)
{
	cv::Ptr<cv::FeatureDetector> detector=cv::ORB::create();;
    cv::Ptr<cv::DescriptorExtractor> descriptor=cv::ORB::create();

	detector->detect(f.rgb,f.kp);
	descriptor->compute(f.rgb,f.kp,f.desp);
	
	return;
}

//估计相机运动
//有足够的inliers返回1,否则返回0
int estimateMotion(FRAME& frame1,FRAME& frame2,CAMERA_INTRINSIC_PARAMETERS& C,cv::Mat& rvec,cv::Mat& tvec,cv::Mat& inliers)
{
	//匹配描述子
	vector<cv::DMatch> matches;
	cv::BFMatcher matcher;
	matcher.match(frame1.desp,frame2.desp,matches);
	cout<<"Find total "<<matches.size()<<"matches."<<endl;
	
	//筛选匹配，把距离太大的去掉
	//这里使用的准则是去掉大于10倍最小距离的匹配（经验值，可改）
	vector<cv::DMatch> goodMatches;
	double minDis=9999;
	for(size_t i=0;i<matches.size();i++)
	{
		if(matches[i].distance<minDis)
			minDis=matches[i].distance;
	}
	cout<<"min dis = "<<minDis<<endl;

	for(size_t i=0;i<matches.size();i++)
	{
		if(matches[i].distance<10*minDis)
			goodMatches.push_back(matches[i]);
	}

	vector<cv::Point3f> pts_obj;
	vector<cv::Point2f> pts_img;

	for(size_t i=0;i<goodMatches.size();i++)
	{
		//query 是第一个，train是第二个
		cv::Point2f p=frame1.kp[goodMatches[i].queryIdx].pt;
		//获取d要小心！x是向右的，y是向下的，所以y才是行，x是列！
		ushort d=frame1.depth.ptr<ushort>(int(p.y))[int(p.x)];	
		if(d==0)
			continue;
		pts_img.push_back(cv::Point2f(frame2.kp[goodMatches[i].trainIdx].pt));
	
		//将（u,v,d）转换成（x,y,z）
		cv::Point3f pt(p.x,p.y,d);
		cv::Point3f pd=point2dTo3d(pt,C);
		pts_obj.push_back(pd);
	}
	cout<<RESET"inliers: "<<pts_obj.size()<<endl;
	if(pts_obj.size()<5)
	{
		cout<<RED" no enourh inliers!"<<endl;
		return 0;
	}
		double camera_matrix_data[3][3]={
		{C.fx,0,C.cx},
		{0,C.fy,C.cy},
		{0,0,1}
	};
	//构建相机矩阵
	cv::Mat cameraMatrix(3,3,CV_64F,camera_matrix_data);
	//求解pnp
	cv::solvePnPRansac( pts_obj, pts_img, cameraMatrix, cv::Mat(), rvec, tvec, false, 100, 1.0, 0.99, inliers );
	cout<<RESET"R="<<rvec<<endl;
	cout<<"t="<<tvec<<endl;
	return 1;
}

//由rgb图和深度图产生点云
void createPCL(PointCloud::Ptr& cloud,FRAME& f,CAMERA_INTRINSIC_PARAMETERS& camera)
{
	for(int m=0;m<f.depth.rows;m++)
		for(int n=0;n<f.depth.cols;n++)
		{
			ushort d=f.depth.ptr<ushort>(m)[n];
			//d可能没有值，没有则跳过此点
			if(d==0)
				continue;
			//d存在值，则想点云增加一个点
			PointT p;

			//计算这个点的控件坐标
			p.z=double(d)/camera.scale;
			p.x=(n-camera.cx)*p.z/camera.fx;
			p.y=(m-camera.cy)*p.z/camera.fy;

			//从rgb中获取它的颜色
			//rgb是三通道的BGR图像，所以需要按照这样的顺序
			p.b=f.rgb.ptr<uchar>(m)[n*3];
			p.g=f.rgb.ptr<uchar>(m)[n*3+1];
			p.r=f.rgb.ptr<uchar>(m)[n*3+2];
			//把p加入到点云中
			cloud->points.push_back(p);
		}
	//设置并保存点云
	cloud->height=1;
	cloud->width = cloud->points.size();
	cout<<"point cloud size="<<cloud->points.size()<<endl;
	cloud->is_dense=false;
	return;
}

//把旋转矩阵和旋转向量转换成为SE(3)
Eigen::Isometry3d rtvec2Isometry3d(cv::Mat& rvec,cv::Mat& tvec)
{
	//将旋转向量转化为旋转矩阵	
	cv::Mat R;
	cv::Rodrigues(rvec,R);
	Eigen::Matrix3d r;
	cv::cv2eigen(R,r);

	//由旋转向量rvec和平移向量tvec得到SE（3）T
	//T是SE(3)特殊欧式群里的元素
	Eigen::Isometry3d T = Eigen::Isometry3d::Identity();

	Eigen::AngleAxisd angle(r);
	T=angle;
	T(0,3) =tvec.at<double>(0,0); 
    T(1,3) = tvec.at<double>(1,0); 
    T(2,3) = tvec.at<double>(2,0);
	return T;
}

//拼接点云
//把cloud1通过rvec和tvec转换成cloud2坐标系下的点云与cloud2相加，并保存在cloud2中
PointCloud::Ptr jointPointCloud(PointCloud::Ptr& cloud1,FRAME& frame,cv::Mat& rvec,cv::Mat& tvec,CAMERA_INTRINSIC_PARAMETERS& C)
{
	
	PointCloud::Ptr cloud2(new PointCloud());
	createPCL(cloud2,frame,C);
	//将旋转向量转化为旋转矩阵	
	cv::Mat R;
	cv::Rodrigues(rvec,R);
	Eigen::Matrix3d r;
	cv::cv2eigen(R,r);

	//由旋转向量rvec和平移向量tvec得到SE（3）T
	//T是SE(3)特殊欧式群里的元素
	Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
	Eigen::AngleAxisd angle(r);
	T=angle;
	T(0,3) =tvec.at<double>(0,0); 
    T(1,3) = tvec.at<double>(1,0); 
    T(2,3) = tvec.at<double>(2,0);
	cout<<"T= "<<T.matrix()<<endl;

	//点云转换与拼接
	PointCloud::Ptr output_(new PointCloud);
	pcl::transformPointCloud(*cloud1,*output_,T.matrix());
	*cloud2+=*output_;

	//Voxel grid 滤波降采样
	static pcl::VoxelGrid<PointT> voxel;
	double gridsize = 0.01;
	voxel.setLeafSize(gridsize,gridsize,gridsize);
	voxel.setInputCloud(cloud2);
	PointCloud::Ptr tmp(new PointCloud());
	voxel.filter(*tmp);
	return tmp;
}
