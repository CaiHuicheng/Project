#include<base.h>
#include<sstream>
//additive pcl
double max_norm=0.2;
// 度量运动的大小
double normofTransform( cv::Mat rvec, cv::Mat tvec );
int main()
{
	//变量初始化
	vector<FRAME> frames;
	cv::Mat rvec,tvec,inliers;
	PointCloud::Ptr output(new PointCloud());
	string s_rgb_dir="/media/jlm/00033B8F000A8AC3/JLM/SLAM/DATASETS/ORB-d/rgb_png/";
	string s_depth_dir="/media/jlm/00033B8F000A8AC3/JLM/SLAM/DATASETS/ORB-d/depth_png/";
	CAMERA_INTRINSIC_PARAMETERS C;
	C.scale=1000;
	C.cx=325.5;
	C.cy=253.5;
	C.fx=518.0;
	C.fy=519.0;
	double gridsize=0.1;
	pcl::visualization::CloudViewer viewer("viewer");

	//设置滤波参数
	pcl::VoxelGrid<PointT> voxel;//网格滤波器，调整地图分辨率
	pcl::PassThrough<PointT> pass;//由于rgbd相机的有效深度有限，把太远的去掉	
	pass.setFilterFieldName("z");//z方向区间滤波器
	pass.setFilterLimits(0.0,4.0);//4m以上就舍弃
	voxel.setLeafSize(gridsize,gridsize,gridsize);

	
	FRAME frame1;
	frame1.rgb=cv::imread("/media/jlm/00033B8F000A8AC3/JLM/SLAM/DATASETS/ORB-d/rgb_png/1.png");
	frame1.depth=cv::imread("/media/jlm/00033B8F000A8AC3/JLM/SLAM/DATASETS/ORB-d/depth_png/1.png",-1);
	computeDetectorAndDescriptor(frame1);
	generatePointCloud(output,frame1,C);
	frames.push_back(frame1);
	for(size_t i=2;i<500;i++)
	{
		cout<<RESET"processing the "<<i<<"  file"<<endl;
		FRAME frame;
		stringstream ss;
		ss<<s_rgb_dir<<i<<".png";
		string s=ss.str();
		ss.str("");
		frame.rgb=cv::imread(s);
		ss<<s_depth_dir<<i<<".png";
		s=ss.str();
		frame.depth=cv::imread(s,-1);
		ss.str("");
		computeDetectorAndDescriptor(frame);
		frames.push_back(frame);
		
		if(!estimateMotion(frames[i-2],frames[i-1],C,rvec,tvec,inliers))	
			continue;//没有足够的内点就跳过这一帧
		double norm=normofTransform(rvec,tvec);
		if(norm>max_norm)
		{
			cout<<RED"move too large!"<<endl;
			continue;
		}//运动过大则跳过
		Eigen::Isometry3d T=rtvec2Isometry3d(rvec,tvec);
		//点云转换与拼接
		output=jointPointCloud(output,frames[i-1],rvec,tvec,C);
		//pcl可视化
		viewer.showCloud(output);
	}
	for(size_t i=0;i<output->points.size();i++)
	{
		output->points[i].y=-output->points[i].y;
		output->points[i].z=-output->points[i].z;
	}
	//存储
	pcl::io::savePCDFile("./result.pcd",*output);
	cout<<RESET"Final map is saved. "<<endl;
	return 0;
}
double normofTransform( cv::Mat rvec, cv::Mat tvec )
{
    return fabs(min(cv::norm(rvec), 2*M_PI-cv::norm(rvec)))+ fabs(cv::norm(tvec));
}
