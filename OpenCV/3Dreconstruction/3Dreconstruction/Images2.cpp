#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include <iostream>
#include <fstream>
//Eigen
#include<Eigen/Core>
#include<Eigen/Geometry>
#include<Eigen/Dense>
//openCV
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/eigen.hpp>
//pcl
#include <pcl/registration/ia_ransac.h>//����һ����
#include <pcl/filters/random_sample.h>//��ȡ�̶������ĵ���
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/rops_estimation.h>
#include <pcl/features/fpfh.h>
#include <pcl/features/vfh.h>
#include <pcl/features/3dsc.h>
#include <pcl/search/kdtree.h>
#include <pcl/filters/filter.h>//
#include <pcl/registration/icp.h>//icp��׼
#include <pcl/visualization/pcl_visualizer.h>//���ӻ�
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/registration/icp.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/common/transforms.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/extract_indices.h>

using namespace std;
using namespace cv;

//pcl ��������
typedef pcl::PointXYZRGBA Point3D;
typedef pcl::PointCloud<Point3D> PointCloud;
//using pcl::NormalEstimation;
//using pcl::search::KdTree;
//typedef pcl::PointXYZ Point3D;
//typedef pcl::PointCloud<Point3D> PointCloudXYZ;
//������������ת��������S
const double S = 1000;//5000 1000  
					  //����ڲ�  fx 0 cx 0 fy cy 0 0 1
					  // ���� ��520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1
					  // bear �� fx=614.2888, fy=614.3722, cx=321.6398, cy=237.2958
					  /*
					  635.59 0 331.45 0 635.59 230.10 0 0 1
					  */
					  //dabai
const double cx = 331.45;
const double fx = 635.59;
const double fy = 635.59;
const double cy = 230.10;
//bear
//const double cx = 321.6398;
//const double fx = 614.2888;
//const double fy = 614.2888;
//const double cy = 237.2958;
//����
//const double cx = 325.1;
//const double fx = 521.0;
//const double fy = 521.0;
//const double cy = 249.7;
//additive pcl
//additive pcl
double normICP = 0.5;

struct FRAME
{
	Mat rgb, depth;
	vector<KeyPoint> kp;
	Mat desp;
};
//������ȡͼƬ
void imageFile(string filename, vector<string> &imageList);

//point2dTo3d
Point3f point2dTo3d(Point3f& point);

//���RT
int estimateMotion(FRAME& frame1, FRAME& frame2, Mat& r, Mat& t, cv::Mat& inliers);

//RGB��depth�����Ƶ�
void createPCL(PointCloud::Ptr& cloud, FRAME& f,Mat& r, Mat& t);
//����Ԥ����
bool splitRemovePlane(PointCloud::Ptr& output);
//����ת�������ת����ת����ΪSE(3)
Eigen::Isometry3d rtvec2Isometry3d(Mat& r, Mat& t);
//ƴ�ӵ���
//��outputͨ��R��Tת����cloud����ϵ�µĵ�����cloud���
PointCloud::Ptr joinPCL(PointCloud::Ptr& cloud1, FRAME& frame, Mat& r, Mat& t);
//��������˶���Ĳ���ICPƥ��
//PointCloud::Ptr joinPCL(PointCloud::Ptr& output, FRAME& frame);
// ����RT�ı任��С
double normofTransform(Mat r, Mat t);

int main(int argc, char** argv)
{
	//string rgb_dir = "color_"; 
	//string depth_dir = "depth_";
	string rgb_dir = "J:/JustIT-USY/CaiHuicheng-practice/OpenCV/3Dreconstruction/3Dreconstruction/data/dabai/color/color_";
	//J:/JustIT-USY/CaiHuicheng-practice/OpenCV/3Dreconstruction/3Dreconstruction/data/output0/color
	string depth_dir = "J:/JustIT-USY/CaiHuicheng-practice/OpenCV/3Dreconstruction/3Dreconstruction/data/dabai/depth/depth_";
	//vector<string> imageList;
	//imageFile("PictureData.txt", imageList);
	//������ʼ��
	vector<FRAME> frames;
	Mat r, t, inliers;
	PointCloud::Ptr output(new PointCloud());
	pcl::visualization::CloudViewer viewer("viewer");

	//��ȡ�ļ���һ��ͼƬ
	FRAME frame1;
	frame1.rgb = imread("J:/JustIT-USY/CaiHuicheng-practice/OpenCV/3Dreconstruction/3Dreconstruction/data/dabai/color/color_0.png");
	frame1.depth = imread("J:/JustIT-USY/CaiHuicheng-practice/OpenCV/3Dreconstruction/3Dreconstruction/data/dabai/depth/depth_0.png", -1);
	//frame1.rgb = imread("color_0.png");
	//frame1.depth = imread("depth_0.png");
	cout << "\nprocessing the 1 images" << endl;
	createPCL(output, frame1,r,t);
	frames.push_back(frame1);
	/*PointCloud::Ptr cloud1show(new PointCloud());
	pcl::visualization::CloudViewer viewer1("cloud1show");
	*cloud1show += *output;*/
	int j = 0;
	for (int i = 1; i < 17; i++)
	{
		stringstream S_RGB_DIR;
		stringstream S_DEPTH_DIR;
		cout << "processing the " << i << " images" << endl;
		FRAME frame;
		S_RGB_DIR << rgb_dir << i << ".png";
		cout << S_RGB_DIR.str() << endl;
		string s = S_RGB_DIR.str();
		frame.rgb = imread(s);
		S_DEPTH_DIR << depth_dir << i << ".png";
		s = S_DEPTH_DIR.str();
		cout << S_DEPTH_DIR.str() << endl;
		frame.depth = imread(s, -1);
		frames.push_back(frame);
		if (!estimateMotion(frames[j], frames[j + 1], r, t, inliers))
		{
			frames.pop_back();
			continue;//û���㹻�ĵ��������һ֡
		}
		double norm = normofTransform(r, t);
		cout << "====================    norm = " << norm << endl;
		if (norm > normICP) {
			frames.pop_back();
			continue;//û���㹻�ĵ��������һ֡
		}
		cout << "SE(3)ƴ��..." << endl;
		output = joinPCL(output, frames[j + 1], r, t);
		//Eigen::Isometry3d T = rtvec2Isometry3d(r, t);

		j++;
	}
	for (size_t i = 0; i < output->points.size(); i++)
	{
		output->points[i].y = -output->points[i].y;
		output->points[i].z = -output->points[i].z;
	}
	//pcl���ӻ�
	viewer.showCloud(output);
	//viewer1.showCloud(cloud1show);

	//�洢
	pcl::io::savePCDFile("./result.pcd", *output);
	cout << "Final map is saved. " << endl;
	system("pause");
	while (!viewer.wasStopped())
	{

	}
	/*while (!viewer1.wasStopped()) {

	}*/
	return 0;
}

double normofTransform(Mat r, Mat t)
{
	double normT = fabs(min(norm(r), 2 * M_PI - norm(r))) + fabs(norm(t));
	return normT;
}

/*��ȡimageName����imageList*/
void imageFile(string filename, vector<string> &imageList)
{
	ifstream file(filename);
	string str;
	while (!file.eof())
	{
		file >> str;
		if (!str.empty()) imageList.push_back(str);
	}
	file.close();
}

Point3f point2dTo3d(Point3f& point)
{
	Point3f p; // 3D��
	p.z = double(point.z) / S;
	p.x = (point.x - cx) * p.z / fx;
	p.y = (point.y - cy) * p.z / fy;
	return p;
}


int estimateMotion(FRAME& frame1, FRAME& frame2, Mat& r, Mat& t, Mat& inliers)
{
	// used in OpenCV3
	vector<DMatch> matches;
	Ptr<FeatureDetector> detector = ORB::create();
	Ptr<DescriptorExtractor> descriptor = ORB::create();
	//������ͼ���е�BRIEF�����ӽ���ƥ�䣬ʹ�� Hamming ����
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
	detector->detect(frame1.rgb, frame1.kp);
	detector->detect(frame2.rgb, frame2.kp);
	descriptor->compute(frame1.rgb, frame1.kp, frame1.desp);
	descriptor->compute(frame2.rgb, frame2.kp, frame2.desp);
	matcher->match(frame1.desp, frame2.desp, matches);
	cout << "Find total " << matches.size() << "matches." << endl;
	vector<DMatch> goodMatches;
	double minDis = 10000;
	for (size_t i = 0; i<matches.size(); i++)
	{
		if (matches[i].distance<minDis)
			minDis = matches[i].distance;
	}
	cout << "min dis = " << minDis << endl;

	for (size_t i = 0; i<matches.size(); i++)
	{
		if (matches[i].distance <= max(2 * minDis, 30.0))
			goodMatches.push_back(matches[i]);
	}

	vector<Point3f> pts_obj;
	vector<Point2f> pts_img;

	for (size_t i = 0; i<goodMatches.size(); i++)
	{
		Point2f p = frame1.kp[goodMatches[i].queryIdx].pt;
		ushort d = frame1.depth.ptr<ushort>(int(p.y))[int(p.x)];
		if (d == 0)
			continue;
		pts_img.push_back(cv::Point2f(frame2.kp[goodMatches[i].trainIdx].pt));

		//u,v,d --�� x,y,z
		cv::Point3f pt(p.x, p.y, d);
		cv::Point3f pd = point2dTo3d(pt);
		pts_obj.push_back(pd);
	}
	cout << "inliers: " << pts_obj.size() << endl;
	/*if (pts_obj.size()<5)
	{
	cout << " no enourh inliers!" << endl;
	return 0;
	}*/
	double camera_matrix_data[3][3] = {
		{ fx,0,cx },
		{ 0,fy,cy },
		{ 0,0,1 }
	};
	//�������
	Mat cameraMatrix(3, 3, CV_64F, camera_matrix_data);
	//���pnp
	cv::solvePnPRansac(pts_obj, pts_img, cameraMatrix, Mat(), r, t, false, 100, 1.0, 0.99, inliers);
	cout << "R=" << r << endl;
	cout << "t=" << t << endl;
	return 1;
}


void createPCL(PointCloud::Ptr& cloud, FRAME& f,Mat& r,Mat& t)
{
	if (!r.data&&!t.data)
	{
		cout << "depth num= " << f.depth.size() << endl;
		for (int m = 0; m<f.depth.rows; m++)
			for (int n = 0; n<f.depth.cols; n++)
			{
				ushort d = f.depth.ptr<ushort>(m)[n];
				//�ų� bad ��
				if (d == 0)
					continue;
				Point3D p;
				//��������������
				p.z = double(d) / S;
				p.x = (n - cx)*p.z / fx;
				p.y = (m - cy)*p.z / fy;

				p.b = f.rgb.ptr<uchar>(m)[n * 3];
				p.g = f.rgb.ptr<uchar>(m)[n * 3 + 1];
				p.r = f.rgb.ptr<uchar>(m)[n * 3 + 2];

				cloud->points.push_back(p);
			}
	}else{
		Eigen::Isometry3d T = rtvec2Isometry3d(r, t);
		cout << "depth num= " << f.depth.size() << endl;
		cout << "T = " << endl;
		cout << T.matrix() << endl;
		for (int m = 0; m<f.depth.rows; m++)
			for (int n = 0; n<f.depth.cols; n++)
			{
				ushort d = f.depth.ptr<ushort>(m)[n];
				//�ų� bad ��
				if (d == 0)
					continue;
				Point3D p;
				Eigen::Vector3d point;
				//��������������
				point[2] = double(d) / S;
				point[1] = (n - cx)*p.z / fx;
				point[0] = (m - cy)*p.z / fy;

				Eigen::Vector3d pointWorld = T*point;
				p.z = pointWorld[2];
				p.x = pointWorld[1];
				p.y = pointWorld[0];
				p.b = f.rgb.ptr<uchar>(m)[n * 3];
				p.g = f.rgb.ptr<uchar>(m)[n * 3 + 1];
				p.r = f.rgb.ptr<uchar>(m)[n * 3 + 2];

				cloud->points.push_back(p);
			}
	}
	//�������
	cloud->height = 1;
	cloud->width = cloud->points.size();
	cout << "point cloud size=" << cloud->points.size() << endl;
	cloud->is_dense = false;
	//���ƴ���
	splitRemovePlane(cloud);
}

Eigen::Isometry3d rtvec2Isometry3d(Mat& r, Mat& t)
{
	//��ת����	
	cv::Mat R;
	cv::Rodrigues(r, R);
	Eigen::Matrix3d rve;
	cv::cv2eigen(R, rve);
	// ����ת����r��ƽ������t�õ�SE��3��T
	//T��SE(3)����ŷʽȺ���Ԫ��
	Eigen::Isometry3d T = Eigen::Isometry3d::Identity();

	Eigen::AngleAxisd angle(rve);
	T = angle;
	T(0, 3) = t.at<double>(0, 0);
	T(1, 3) = t.at<double>(1, 0);
	T(2, 3) = t.at<double>(2, 0);
	return T;
}

/*PointCloudXYZ::Ptr XYZRGBtoXYZ(PointCloud::Ptr& cloud) {
PointCloudXYZ::Ptr output(new PointCloudXYZ);
for (size_t i = 0; i < cloud->points.size(); i++)
{
Point3D p;
p.x = cloud->points[i].x;
p.y = cloud->points[i].y;
p.z = cloud->points[i].z;

output->points.push_back(p);

}
return output;
}
*/

bool splitRemovePlane(PointCloud::Ptr& output) {
	pcl::PointCloud<Point3D>::Ptr cloud_filtered(new pcl::PointCloud<Point3D>);
	//ƽ��ָ�ȥ��ƽ��
	pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
	pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
	// Create the segmentation object
	pcl::SACSegmentation<Point3D> seg;
	//��ѡ����
	seg.setOptimizeCoefficients(true);
	// ��ѡ����
	seg.setModelType(pcl::SACMODEL_PLANE);
	seg.setMethodType(pcl::SAC_RANSAC);
	// ������ֵ ��λm
	seg.setDistanceThreshold(0.01);
	seg.setInputCloud(output);
	seg.segment(*inliers, *coefficients);
	if (inliers->indices.size() == 0)
	{
		PCL_ERROR("Could not estimate a planar model for the given dataset.");
	}
	// ��ȡ����
	pcl::ExtractIndices<Point3D> extract;
	extract.setInputCloud(output);
	extract.setIndices(inliers);
	//��ȡ���� ���屳��
	//extract.filter(*cloud_filtered);
	//std::cerr << "Ground cloud after filtering: " << std::endl;
	//std::cerr << *cloud_filtered << std::endl;
	//pcl::PCDWriter writer;
	//writer.write<pcl::Point3D>("3dpoints_ground.pcd", *cloud_filtered, false);

	// ��ȡ�������������
	extract.setNegative(true);
	extract.filter(*cloud_filtered);

	std::cerr << "Object cloud after filtering: " << std::endl;
	std::cerr << *cloud_filtered << std::endl;
	output = cloud_filtered;
	if (output->points.size()) {
		cout << "split cloud size = " << output->points.size() << endl;
		return true;
	}
	else {
		return false;
	}
}

PointCloud::Ptr joinPCL(PointCloud::Ptr& output, FRAME& frame, Mat& r, Mat& t)
{

	PointCloud::Ptr cloud(new PointCloud());
	createPCL(cloud, frame,r,t);
	//����ת����ƴ��
	*output += *cloud;
	cout << "����ƴ��ͼ��..." << endl;

	//Voxel grid �˲�������
	pcl::VoxelGrid<Point3D> voxel;//�����˲�����������ͼ�ֱ���
	pcl::PassThrough<Point3D> pass;//����rgbd�������Ч������ޣ���̫Զ��ȥ��	
	pass.setFilterFieldName("z");//z���������˲���
	pass.setFilterLimits(0.0, 0.1);//4m���Ͼ�����
	double gridsize = 0.0001;
	voxel.setLeafSize(gridsize, gridsize, gridsize);
	voxel.setInputCloud(output);
	PointCloud::Ptr tmp(new PointCloud());
	voxel.filter(*tmp);
	return tmp;
}
/*PointCloud::Ptr joinPCL(PointCloud::Ptr& output, FRAME& frame)
{

	PointCloud::Ptr cloud(new PointCloud());
	createPCL(cloud, frame);
	cout << "=========================cloud = " << cloud->points.size() << endl;
	//ICP �ڲ�֪������ڲ�ʱ����ICPƥ����� ��ñ任����
	/*
	//ȥ��Դ���ƺ�Ŀ������е���Ч��
	//���ص����ļ�
	PointCloudXYZ::Ptr cloud_src_o(new PointCloudXYZ);//ԭ���ƣ�����׼
	PointCloudXYZ::Ptr cloud_tgt_o(new PointCloudXYZ);//Ŀ�����
	cloud_src_o = XYZRGBtoXYZ(output);
	cloud_tgt_o = XYZRGBtoXYZ(cloud);
	cout << "cloud = " << cloud_src_o->points.size() << endl;
	clock_t start = clock();

	//ȥ��NAN��
	vector<int> indices_src; //����ȥ���ĵ������
	pcl::removeNaNFromPointCloud(*cloud_src_o, *cloud_src_o, indices_src);
	cout << "remove *cloud_src_o nan" << endl;

	vector<int> indices_tgt;
	pcl::removeNaNFromPointCloud(*cloud_tgt_o, *cloud_tgt_o, indices_tgt);
	cout << "remove *cloud_tgt_o nan" << endl;

	//�²����˲�
	pcl::VoxelGrid<pcl::PointXYZ> voxel_grid;
	voxel_grid.setLeafSize(0.012, 0.012, 0.012);
	voxel_grid.setInputCloud(cloud_src_o);
	PointCloudXYZ::Ptr cloud_src(new PointCloudXYZ);
	voxel_grid.filter(*cloud_src);
	cout << "down size *cloud_src_o from " << cloud_src_o->points.size() << "to" << cloud_src->points.size() << endl;

	pcl::VoxelGrid<pcl::PointXYZ> voxel_grid_2;
	voxel_grid_2.setLeafSize(0.012, 0.012, 0.012);
	voxel_grid_2.setInputCloud(cloud_tgt_o);
	PointCloudXYZ::Ptr cloud_tgt(new PointCloudXYZ);
	voxel_grid_2.filter(*cloud_tgt);
	cout << "down size *cloud_tgt_o from " << cloud_tgt_o->points.size() << "to" << cloud_tgt->points.size() << endl;


	//������淨��
	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne_src;
	ne_src.setInputCloud(cloud_src);
	pcl::search::KdTree< pcl::PointXYZ>::Ptr tree_src(new pcl::search::KdTree< pcl::PointXYZ>());
	ne_src.setSearchMethod(tree_src);
	pcl::PointCloud<pcl::Normal>::Ptr cloud_src_normals(new pcl::PointCloud< pcl::Normal>);
	ne_src.setRadiusSearch(0.02);
	ne_src.compute(*cloud_src_normals);

	pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne_tgt;
	ne_tgt.setInputCloud(cloud_tgt);
	pcl::search::KdTree< pcl::PointXYZ>::Ptr tree_tgt(new pcl::search::KdTree< pcl::PointXYZ>());
	ne_tgt.setSearchMethod(tree_tgt);
	pcl::PointCloud<pcl::Normal>::Ptr cloud_tgt_normals(new pcl::PointCloud< pcl::Normal>);
	//ne_tgt.setKSearch(20);
	ne_tgt.setRadiusSearch(0.02);
	ne_tgt.compute(*cloud_tgt_normals);

	//����FPFH
	pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh_src;
	fpfh_src.setInputCloud(cloud_src);
	fpfh_src.setInputNormals(cloud_src_normals);
	pcl::search::KdTree<Point3D>::Ptr tree_src_fpfh(new pcl::search::KdTree<Point3D>);
	fpfh_src.setSearchMethod(tree_src_fpfh);
	pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhs_src(new pcl::PointCloud<pcl::FPFHSignature33>());
	fpfh_src.setRadiusSearch(0.05);
	fpfh_src.compute(*fpfhs_src);
	std::cout << "compute *cloud_src fpfh" << endl;

	pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh_tgt;
	fpfh_tgt.setInputCloud(cloud_tgt);
	fpfh_tgt.setInputNormals(cloud_tgt_normals);
	pcl::search::KdTree<Point3D>::Ptr tree_tgt_fpfh(new pcl::search::KdTree<Point3D>);
	fpfh_tgt.setSearchMethod(tree_tgt_fpfh);
	pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhs_tgt(new pcl::PointCloud<pcl::FPFHSignature33>());
	fpfh_tgt.setRadiusSearch(0.05);
	fpfh_tgt.compute(*fpfhs_tgt);
	std::cout << "compute *cloud_tgt fpfh" << endl;

	//SAC��׼
	pcl::SampleConsensusInitialAlignment<pcl::PointXYZ, pcl::PointXYZ, pcl::FPFHSignature33> scia;
	scia.setInputSource(cloud_src);
	scia.setInputTarget(cloud_tgt);
	scia.setSourceFeatures(fpfhs_src);
	scia.setTargetFeatures(fpfhs_tgt);
	//scia.setMinSampleDistance(1);
	//scia.setNumberOfSamples(2);
	//scia.setCorrespondenceRandomness(20);
	PointCloudXYZ::Ptr sac_result(new PointCloudXYZ);
	scia.align(*sac_result);
	std::cout << "sac has converged:" << scia.hasConverged() << "  score: " << scia.getFitnessScore() << endl;
	Eigen::Matrix4f sac_trans;
	sac_trans = scia.getFinalTransformation();
	std::cout << sac_trans << endl;
	//pcl::io::savePCDFileASCII("bunny_transformed_sac.pcd", *sac_result);
	clock_t sac_time = clock();

	//icp��׼
	PointCloudXYZ::Ptr icp_result(new PointCloudXYZ);
	pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
	icp.setInputSource(cloud_src);
	icp.setInputTarget(cloud_tgt_o);
	//Set the max correspondence distance to 4cm (e.g., correspondences with higher distances will be ignored)
	icp.setMaxCorrespondenceDistance(0.04);
	// ����������
	icp.setMaximumIterations(100);
	// ���α仯����֮��Ĳ�ֵ
	icp.setTransformationEpsilon(1e-10);
	// �������
	icp.setEuclideanFitnessEpsilon(0.01);
	icp.align(*icp_result, sac_trans);

	clock_t end = clock();
	cout << "total time: " << (double)(end - start) / (double)CLOCKS_PER_SEC << " s" << endl;
	cout << "sac time: " << (double)(sac_time - start) / (double)CLOCKS_PER_SEC << " s" << endl;
	cout << "icp time: " << (double)(end - sac_time) / (double)CLOCKS_PER_SEC << " s" << endl;

	std::cout << "ICP has converged:" << icp.hasConverged()
	<< " score: " << icp.getFitnessScore() << std::endl;
	Eigen::Matrix4f T;//���� �任���� T
	T = icp.getFinalTransformation();

	pcl::IterativeClosestPoint<Point3D, Point3D> icp;
	icp.setInputSource(output);
	icp.setInputTarget(cloud);
	//�������ã����ֿ�ȱʡ
	//icp.setMaxCorrespondenceDistance(1);	//��Ӧ����������(��λΪm)
	icp.setMaximumIterations(20);           //����������
											//icp.setTransformationEpsilon(1e-6);     //���α仯����֮��Ĳ�ֵ
											//icp.setEuclideanFitnessEpsilon(0.001);  //�������������Ǿ�������С����ֵ�� ֹͣ����
	icp.align(*cloud);         //�任���Դ����
	Eigen::Matrix4f T = Eigen::Matrix4f::Identity();//���� �任���� T
	if (icp.hasConverged())
	{
		//�����������������˵�������������������
		cout << "T =" << icp.getFitnessScore() << "\n" << endl;

		//����任���� T
		T = icp.getFinalTransformation();
		cout << T << endl;
	}
	else
		cout << "Not converged." << endl;
	//����ת����ƴ��
	PointCloud::Ptr output_(new PointCloud);
	pcl::transformPointCloud(*output, *output_, T);
	*cloud += *output_;
	//Voxel grid �˲�������
	//�����˲�����
	pcl::VoxelGrid<Point3D> voxel;//�����˲�����������ͼ�ֱ���
	pcl::PassThrough<Point3D> pass;//����rgbd�������Ч������ޣ���̫Զ��ȥ��	
	pass.setFilterFieldName("z");//z���������˲���
	pass.setFilterLimits(0.0, 4.0);//4m���Ͼ�����
	double gridsize = 0.01;
	voxel.setLeafSize(gridsize, gridsize, gridsize);
	voxel.setInputCloud(cloud);
	PointCloud::Ptr tmp(new PointCloud());
	voxel.filter(*tmp);
	return tmp;
}
*/