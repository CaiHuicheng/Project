#include<iostream>
#include<vector>
using namespace std;
//openCV�û�����ģ��
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
//OpenCV�������ģ��
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/calib3d/calib3d.hpp>
//for pcl
#include <pcl/common/transforms.h>
#include <pcl/visualization/cloud_viewer.h>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>

//Eigen!
#include<Eigen/Core>
#include<Eigen/Geometry>

//�����������
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;

//����ڲ�
struct CAMERA_INTRINSIC_PARAMETERS
{
	double cx,cy,fx,fy,scale;
};

struct FRAME
{
	cv::Mat rgb,depth;
	vector<cv::KeyPoint> kp;
	cv::Mat desp;
};
//point2dT03d ���������ͼ��ת����Ϊ�ռ�����
//input:3ά��Point3f(u,v,d)
cv::Point3f point2dTo3d(cv::Point3f& point,CAMERA_INTRINSIC_PARAMETERS& camera);


//����ؼ����������
void computeDetectorAndDescriptor(FRAME& f);

//��������˶�
//���㹻��inliers����1,���򷵻�0
int estimateMotion(FRAME& frame1,FRAME& frame2,CAMERA_INTRINSIC_PARAMETERS& camera,cv::Mat& rvec,cv::Mat& tvec,cv::Mat& inliers);

//��rgbͼ�����ͼ��������
void createPCL(PointCloud::Ptr& cloud,FRAME& f,CAMERA_INTRINSIC_PARAMETERS& camera);

//����ת�������ת����ת����ΪSE(3)
Eigen::Isometry3d rtvec2Isometry3d(cv::Mat& rvec,cv::Mat& tvec);
//ƴ�ӵ���
//��cloud1ͨ��rvec��tvecת����cloud2����ϵ�µĵ�����cloud2���
PointCloud::Ptr jointPointCloud(PointCloud::Ptr& cloud1,FRAME& frame,cv::Mat& rvec,cv::Mat& tvec,CAMERA_INTRINSIC_PARAMETERS& C);


//the following are UBUNTU/LINUX ONLY terminal color
#define RESET "\033[0m"
#define BLACK "\033[30m" /* Black */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m" /* Cyan */
#define WHITE "\033[37m" /* White */
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m" /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */
