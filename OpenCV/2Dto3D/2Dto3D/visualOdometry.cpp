#include"base.h"
#include<sstream>
//additive pcl
double max_norm=10;
// �����˶��Ĵ�С
double normofTransform( cv::Mat rvec, cv::Mat tvec );
int main()
{
	//������ʼ��
	vector<FRAME> frames;
	cv::Mat rvec,tvec,inliers;
	PointCloud::Ptr output(new PointCloud());
	string s_rgb_dir="J:/JustIT-USY/CaiHuicheng-practice/OpenCV/3Dreconstruction/3Dreconstruction/data/bear/color/color_";
	string s_depth_dir="J:/JustIT-USY/CaiHuicheng-practice/OpenCV/3Dreconstruction/3Dreconstruction/data/bear/depth/depth_";
	CAMERA_INTRINSIC_PARAMETERS C;
	C.scale=1000;
	C.cx=331.45;
	C.cy=230.10;
	C.fx=635.59;
	C.fy=635.59;
	double gridsize=0.1;
	pcl::visualization::CloudViewer viewer("viewer");

	//�����˲�����
	pcl::VoxelGrid<PointT> voxel;//�����˲�����������ͼ�ֱ���
	pcl::PassThrough<PointT> pass;//����rgbd�������Ч������ޣ���̫Զ��ȥ��	
	pass.setFilterFieldName("z");//z���������˲���
	pass.setFilterLimits(0.0,4.0);//4m���Ͼ�����
	voxel.setLeafSize(gridsize,gridsize,gridsize);

	
	FRAME frame1;
	frame1.rgb=cv::imread("J:/JustIT-USY/CaiHuicheng-practice/OpenCV/3Dreconstruction/3Dreconstruction/data/dabai/color/color_0.png");
	frame1.depth=cv::imread("J:/JustIT-USY/CaiHuicheng-practice/OpenCV/3Dreconstruction/3Dreconstruction/data/dabai/depth/depth_0.png",-1);
	computeDetectorAndDescriptor(frame1);
	createPCL(output,frame1,C);
	frames.push_back(frame1);
	int j = 0;
	for(size_t i=1;i<9;i++)
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
		if (!estimateMotion(frames[j], frames[j+1], C, rvec, tvec, inliers))
		{
			frames.pop_back();
			cout << "inliers too little " << endl;
			continue;//û���㹻���ڵ��������һ֡
		}
		double norm=normofTransform(rvec,tvec);
		if(norm>max_norm)
		{
			cout<<"move too large!"<<endl;
			continue;
		}//�˶�����������
		Eigen::Isometry3d T=rtvec2Isometry3d(rvec,tvec);
		//����ת����ƴ��
		output=jointPointCloud(output,frames[j],rvec,tvec,C);
		j++;
	}
	for(size_t i=0;i<output->points.size();i++)
	{
		output->points[i].y=-output->points[i].y;
		output->points[i].z=-output->points[i].z;

	}
	//�洢
	pcl::io::savePCDFile("result.pcd",*output);
	cout<<"Final map is saved. "<<endl;
	system("pause");
	return 0;

}
double normofTransform( cv::Mat rvec, cv::Mat tvec )
{
    return fabs(min(cv::norm(rvec), 2*M_PI-cv::norm(rvec)))+ fabs(cv::norm(tvec));
}
