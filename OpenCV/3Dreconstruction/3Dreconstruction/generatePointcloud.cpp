//const double cx = 331.45;
//const double fx = 635.59;
//const double fy = 635.59;
//const double cy = 230.10;
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
#define _CRT_SECURE_NO_WARNINGS
#include"base.h"
#include <iostream>
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>
#include <vector>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include "pcl/console/print.h"
//�����������
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;
//����ڲ�
//const double fx = 635.59;
//const double fy = 635.59;
//const double cy = 230.10;
const double camera_factor = 1000;
const double camera_cx = 331.45;
const double camera_cy = 230.10;
const double camera_fx = 635.59;
const double camera_fy = 635.59;

int main(int argc, char** argv)
{
	//��ȡ./data/rgb.png��./data/depth.png����ת��Ϊ����

	cv::Mat rgb, depth;
	rgb = cv::imread("0.png");
	depth = cv::imread("d0.png", -1);


	//���Ʊ���
	//ʹ������ָ�룬����һ���յ��ơ�����ָ���������Զ��ͷ�
	PointCloud::Ptr cloud(new PointCloud);
	//�������ͼ
	for (int m = 0; m<depth.rows; m++)
		for (int n = 0; n<depth.cols; n++)
		{
			ushort d = depth.ptr<ushort>(m)[n];
			//d����û��ֵ��û���������˵�
			if (d == 0)
				continue;
			//d����ֵ�������������һ����
			PointT p;

			//���������Ŀؼ�����
			p.z = -double(d) / camera_factor;
			p.x = -(n - camera_cx)*p.z / camera_fx;
			p.y = (m - camera_cy)*p.z / camera_fy;

			//��rgb�л�ȡ������ɫ
			//rgb����ͨ����BGRͼ��������Ҫ����������˳��
			p.b = rgb.ptr<uchar>(m)[n * 3];
			p.g = rgb.ptr<uchar>(m)[n * 3 + 1];
			p.r = rgb.ptr<uchar>(m)[n * 3 + 2];
			//��p���뵽������
			cloud->points.push_back(p);
		}
	
	/*pcl::search::Search<PointT>::Ptr tree(new pcl::search::KdTree<PointT>);
	pcl::PointCloud <pcl::Normal>::Ptr normals(new pcl::PointCloud <pcl::Normal>);
	pcl::NormalEstimation<PointT, pcl::Normal> normal_estimator;
	normal_estimator.setSearchMethod(tree);
	normal_estimator.setInputCloud(cloud);
	normal_estimator.setKSearch(50);
	normal_estimator.compute(*normals);

	pcl::IndicesPtr indices(new std::vector <int>);
	pcl::PassThrough<PointT> pass;
	pass.setInputCloud(cloud);
	pass.setFilterFieldName("z");
	pass.setFilterLimits(0.0, 1.0);
	pass.filter(*indices);

	pcl::RegionGrowing<PointT, pcl::Normal> reg;
	reg.setMinClusterSize(50);
	reg.setMaxClusterSize(1000000);
	reg.setSearchMethod(tree);
	reg.setNumberOfNeighbours(30);
	reg.setInputCloud(cloud);
	//reg.setIndices (indices);
	reg.setInputNormals(normals);
	reg.setSmoothnessThreshold(3.0 / 180.0 * M_PI);
	reg.setCurvatureThreshold(1.0);
	std::vector <pcl::PointIndices> clusters;
	reg.extract(clusters);

	std::cout << "Number of clusters is equal to " << clusters.size() << std::endl;
	std::cout << "First cluster has " << clusters[0].indices.size() << " points." << endl;
	std::cout << "These are the indices of the points of the initial" <<
		std::endl << "cloud that belong to the first cluster:" << std::endl;
	int counter = 0;
	while (counter < clusters[0].indices.size())
	{
		std::cout << clusters[0].indices[counter] << ", ";
		counter++;
		if (counter % 10 == 0)
			std::cout << std::endl;
	}
	std::cout << std::endl;
	pcl::PointCloud <pcl::PointXYZRGB>::Ptr colored_cloud = reg.getColoredCloud();*/
	cloud->height = 1;
	cloud->width = cloud->points.size();
	cout << "point cloud size=" << cloud->points.size() << endl;
	cloud->is_dense = false;
	pcl::io::savePCDFile("pointcloud1.pcd", *cloud);
	//��ʾ����
	pcl::visualization::CloudViewer viewer("viewer");
	viewer.showCloud(cloud);
	while (!viewer.wasStopped())
	{

	}
	//������ݲ��˳�
	cloud->points.clear();
	cout << "Point cloud saved." << endl;
	system("pause");
	return 0;
	/*
	// ����kd-tree������������ .
	pcl::search::KdTree<PointT>::Ptr kdtree(new pcl::search::KdTree<PointT>);
	kdtree->setInputCloud(cloud);

	// Euclidean �������.
	pcl::EuclideanClusterExtraction<PointT> clustering;
	// ���þ������Сֵ 2cm (small values may cause objects to be divided
	// in several clusters, whereas big values may join objects in a same cluster).
	clustering.setClusterTolerance(0.02);
	// ���þ����С��������������
	clustering.setMinClusterSize(100);
	clustering.setMaxClusterSize(25000);
	clustering.setSearchMethod(kdtree);
	clustering.setInputCloud(cloud);
	std::vector<pcl::PointIndices> clusters;
	clustering.extract(clusters);
	int currentClusterNum = 1;
	for (std::vector<pcl::PointIndices>::const_iterator i = clusters.begin(); i != clusters.end(); ++i)
	{
		//������еĵ��Ƶ�һ���µĵ�����
		pcl::PointCloud<PointT>::Ptr cluster(new pcl::PointCloud<PointT>);
		for (std::vector<int>::const_iterator point = i->indices.begin(); point != i->indices.end(); point++)
			cluster->points.push_back(cloud->points[*point]);
		cluster->width = cluster->points.size();
		cluster->height = 1;
		cluster->is_dense = true;

		// ����
		if (cluster->points.size() <= 0)
			break;
		std::cout << "Cluster " << currentClusterNum << " has " << cluster->points.size() << " points." << std::endl;
		std::string fileName = "cluster" + boost::to_string(currentClusterNum) + ".pcd";
		pcl::io::savePCDFileASCII(fileName, *cluster);
		currentClusterNum++;
	}*/
	/*//����һ��ģ�Ͳ����������ڼ�¼���
	pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
	//inliers��ʾ��������̵ĵ� ��¼���ǵ��Ƶ����
	pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
	// ����һ���ָ���
	pcl::SACSegmentation<PointT> seg;
	// Optional
	seg.setOptimizeCoefficients (true);
	// Mandatory-����Ŀ�꼸����״
	seg.setModelType (pcl::SACMODEL_LINE);
	//�ָ�������������
	seg.setMethodType (pcl::SAC_RANSAC);
	//����������̷�Χm
	seg.setDistanceThreshold (0.001);
	//	//�������
	seg.setInputCloud (cloud);
	//�ָ����
	seg.segment (*inliers, *coefficients);
	//
	ofstream out;
	out.open("line.txt");
	//out<<coefficients->values[0]<<" "<<coefficients->values[1]<<" "<<coefficients->values[2];
	out<<*coefficients;
	out.close();
	//
	pcl::visualization::CloudViewer viewer("viewer");
	viewer.showCloud(cloud);
	while (!viewer.wasStopped())
	{
	}
	//������ݲ��˳�
	cloud->points.clear();
	cout << "Point cloud saved." << endl;
	system("pause");
	return 0;*/
}
