#include "base.h"
#include <opencv2/core/eigen.hpp>//for cv::cv2eigen

//point2dT03d ���������ͼ��ת����Ϊ�ռ�����
//input:3ά��Point3f(u,v,d)
cv::Point3f point2dTo3d(cv::Point3f& point,CAMERA_INTRINSIC_PARAMETERS& camera)
{
	cv::Point3f p; // 3D ��
    p.z = double( point.z ) / camera.scale;
    p.x = ( point.x - camera.cx) * p.z / camera.fx;
    p.y = ( point.y - camera.cy) * p.z / camera.fy;
    return p;
}

//����ؼ����������
void computeDetectorAndDescriptor(FRAME& f)
{
	cv::Ptr<cv::FeatureDetector> detector=cv::ORB::create();;
    cv::Ptr<cv::DescriptorExtractor> descriptor=cv::ORB::create();

	detector->detect(f.rgb,f.kp);
	descriptor->compute(f.rgb,f.kp,f.desp);
	
	return;
}

//��������˶�
//���㹻��inliers����1,���򷵻�0
int estimateMotion(FRAME& frame1,FRAME& frame2,CAMERA_INTRINSIC_PARAMETERS& C,cv::Mat& rvec,cv::Mat& tvec,cv::Mat& inliers)
{
	//ƥ��������
	vector<cv::DMatch> matches;
	cv::BFMatcher matcher;
	matcher.match(frame1.desp,frame2.desp,matches);
	cout<<"Find total "<<matches.size()<<"matches."<<endl;
	
	//ɸѡƥ�䣬�Ѿ���̫���ȥ��
	//����ʹ�õ�׼����ȥ������10����С�����ƥ�䣨����ֵ���ɸģ�
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
		//query �ǵ�һ����train�ǵڶ���
		cv::Point2f p=frame1.kp[goodMatches[i].queryIdx].pt;
		//��ȡdҪС�ģ�x�����ҵģ�y�����µģ�����y�����У�x���У�
		ushort d=frame1.depth.ptr<ushort>(int(p.y))[int(p.x)];	
		if(d==0)
			continue;
		pts_img.push_back(cv::Point2f(frame2.kp[goodMatches[i].trainIdx].pt));
	
		//����u,v,d��ת���ɣ�x,y,z��
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
	//�����������
	cv::Mat cameraMatrix(3,3,CV_64F,camera_matrix_data);
	//���pnp
	cv::solvePnPRansac( pts_obj, pts_img, cameraMatrix, cv::Mat(), rvec, tvec, false, 100, 1.0, 0.99, inliers );
	cout<<RESET"R="<<rvec<<endl;
	cout<<"t="<<tvec<<endl;
	return 1;
}

//��rgbͼ�����ͼ��������
void createPCL(PointCloud::Ptr& cloud,FRAME& f,CAMERA_INTRINSIC_PARAMETERS& camera)
{
	for(int m=0;m<f.depth.rows;m++)
		for(int n=0;n<f.depth.cols;n++)
		{
			ushort d=f.depth.ptr<ushort>(m)[n];
			//d����û��ֵ��û���������˵�
			if(d==0)
				continue;
			//d����ֵ�������������һ����
			PointT p;

			//���������Ŀؼ�����
			p.z=double(d)/camera.scale;
			p.x=(n-camera.cx)*p.z/camera.fx;
			p.y=(m-camera.cy)*p.z/camera.fy;

			//��rgb�л�ȡ������ɫ
			//rgb����ͨ����BGRͼ��������Ҫ����������˳��
			p.b=f.rgb.ptr<uchar>(m)[n*3];
			p.g=f.rgb.ptr<uchar>(m)[n*3+1];
			p.r=f.rgb.ptr<uchar>(m)[n*3+2];
			//��p���뵽������
			cloud->points.push_back(p);
		}
	//���ò��������
	cloud->height=1;
	cloud->width = cloud->points.size();
	cout<<"point cloud size="<<cloud->points.size()<<endl;
	cloud->is_dense=false;
	return;
}

//����ת�������ת����ת����ΪSE(3)
Eigen::Isometry3d rtvec2Isometry3d(cv::Mat& rvec,cv::Mat& tvec)
{
	//����ת����ת��Ϊ��ת����	
	cv::Mat R;
	cv::Rodrigues(rvec,R);
	Eigen::Matrix3d r;
	cv::cv2eigen(R,r);

	//����ת����rvec��ƽ������tvec�õ�SE��3��T
	//T��SE(3)����ŷʽȺ���Ԫ��
	Eigen::Isometry3d T = Eigen::Isometry3d::Identity();

	Eigen::AngleAxisd angle(r);
	T=angle;
	T(0,3) =tvec.at<double>(0,0); 
    T(1,3) = tvec.at<double>(1,0); 
    T(2,3) = tvec.at<double>(2,0);
	return T;
}

//ƴ�ӵ���
//��cloud1ͨ��rvec��tvecת����cloud2����ϵ�µĵ�����cloud2��ӣ���������cloud2��
PointCloud::Ptr jointPointCloud(PointCloud::Ptr& cloud1,FRAME& frame,cv::Mat& rvec,cv::Mat& tvec,CAMERA_INTRINSIC_PARAMETERS& C)
{
	
	PointCloud::Ptr cloud2(new PointCloud());
	createPCL(cloud2,frame,C);
	//����ת����ת��Ϊ��ת����	
	cv::Mat R;
	cv::Rodrigues(rvec,R);
	Eigen::Matrix3d r;
	cv::cv2eigen(R,r);

	//����ת����rvec��ƽ������tvec�õ�SE��3��T
	//T��SE(3)����ŷʽȺ���Ԫ��
	Eigen::Isometry3d T = Eigen::Isometry3d::Identity();
	Eigen::AngleAxisd angle(r);
	T=angle;
	T(0,3) =tvec.at<double>(0,0); 
    T(1,3) = tvec.at<double>(1,0); 
    T(2,3) = tvec.at<double>(2,0);
	cout<<"T= "<<T.matrix()<<endl;

	//����ת����ƴ��
	PointCloud::Ptr output_(new PointCloud);
	pcl::transformPointCloud(*cloud1,*output_,T.matrix());
	*cloud2+=*output_;

	//Voxel grid �˲�������
	static pcl::VoxelGrid<PointT> voxel;
	double gridsize = 0.01;
	voxel.setLeafSize(gridsize,gridsize,gridsize);
	voxel.setInputCloud(cloud2);
	PointCloud::Ptr tmp(new PointCloud());
	voxel.filter(*tmp);
	return tmp;
}
