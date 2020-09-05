#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 


using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

	/*if (argc != 3)//�ж�����������Դ�
	{
		cout << "usage: feature_extraction img1 img2" << endl;
		return 1;
	}*/

	//��ȡҪƥ�������ͼ��
	Mat img_color1 = imread("color_1.png");//ͼƬ·����.cpp�ļ���һ�𣬻��߾���·��
	Mat img_color2 = imread("color_2.png");//ͼƬ·����.cpp�ļ���һ�𣬻��߾���·��
	Mat img_1;
	Mat img_2;
	cvtColor(img_color1, img_1, CV_BGR2GRAY);
	cvtColor(img_color2, img_2, CV_BGR2GRAY);
	imshow("Grey1", img_1);
	imshow("Grey2", img_2);

	//��ʼ��
	//���ȴ��������ؼ������飬���ڴ������ͼ��Ĺؼ��㣬����Ԫ����KeyPoint����
	std::vector<KeyPoint> keypoints_1, keypoints_2;

	//��������ͼ��������ӣ�������Mat����
	Mat descriptors_1, descriptors_2;

	//����һ��ORB����ָ��orb��ORB���Ǽ̳���Feature2D��
	//class CV_EXPORTS_W ORB : public Feature2D
	//���￴һ��create()Դ�룺�����϶࣬�����ܡ�
	//creat()�������в�������Ĭ��ֵ������static��Ptr<ORB>���͡�
	/*
	CV_WRAP static Ptr<ORB> create(int nfeatures=500,
								   float scaleFactor=1.2f,
								   int nlevels=8,
								   int edgeThreshold=31,
								   int firstLevel=0,
								   int WTA_K=2,
								   int scoreType=ORB::HARRIS_SCORE,
								   int patchSize=31,
								   int fastThreshold=20);
	*/
	//��������������Ǵ���һ��Ptr<ORB>���͵�orb�����ڽ���ORB����create()�����ķ���ֵ
	Ptr<ORB> orb = ORB::create();


	//��һ�������Oriented FAST�ǵ�λ��.
	//detect��Feature2D�еķ�����orb������ָ�룬���Ե���
	//��һ��detect()������ԭ�Ͳ�������Ҫ����ͼ�񣬹ؼ������飬����������ΪĬ��ֵ
	/*
	CV_WRAP virtual void detect( InputArray image,
								 CV_OUT std::vector<KeyPoint>& keypoints,
								 InputArray mask=noArray() );
	*/
	orb->detect(img_1, keypoints_1);
	orb->detect(img_2, keypoints_2);


	//�ڶ��������ݽǵ�λ�ü���BRIEF������
	//compute��Feature2D�еķ�����orb������ָ�룬���Ե���
	//��һ��compute()ԭ�Ͳ�����ͼ��ͼ��Ĺؼ������飬Mat���͵�������
	/*
	CV_WRAP virtual void compute( InputArray image,
								  CV_OUT CV_IN_OUT std::vector<KeyPoint>& keypoints,
								  OutputArray descriptors );
	*/
	orb->compute(img_1, keypoints_1, descriptors_1);
	orb->compute(img_2, keypoints_2, descriptors_2);

	//�����������������ͼƬ��
	Mat outimg1;
	//drawKeypoints()����ԭ�Ͳ�����ԭͼ��ԭͼ�ؼ��㣬���йؼ�������ͼ�񣬺�������ΪĬ��ֵ
	/*
	CV_EXPORTS_W void drawKeypoints( InputArray image,
									 const std::vector<KeyPoint>& keypoints,
									 InputOutputArray outImage,
									 const Scalar& color=Scalar::all(-1),
									 int flags=DrawMatchesFlags::DEFAULT );
	*/
	//ע�⿴�����ﲢû���õ������ӣ������ӵ����������ں���Ĺؼ���ɸѡ��
	drawKeypoints(img_1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	imshow("ORB������", outimg1);


	//��������������ͼ���е�BRIEF�����ӽ���ƥ�䣬ʹ�� Hamming ����

	//����һ��ƥ������飬���ڳн�ƥ�����DMatch����ʵ��match_points_array��Ϊ���С�matches����Ϊ���飬Ԫ������ΪDMatch
	vector<DMatch> matches;

	//����һ��BFMatcherƥ������BFMatcher�๹�캯�����£�������������Ĭ��ֵ�����ǵ�һ��������������ʹ�õĲ�����Ĭ��ֵ�����Ǻ�������
	//CV_WRAP BFMatcher( int normType=NORM_L2, bool crossCheck=false );
	BFMatcher matcher(NORM_HAMMING);

	//����matcher��match��������ƥ��,�����õ��������ӣ�û���ùؼ��㡣
	//ƥ������Ľ��д���Ϸ������matches[]������
	matcher.match(descriptors_1, descriptors_2, matches);

	//���Ĳ�������matches[]���飬�ҳ�ƥ�������������С���룬���ں����ƥ���ɸѡ��
	//����ľ������Ϸ�����ĺ����������飬�����������������ƥ������Ƴ̶ȣ�����Ҳ���ҳ��������ƺ�����Ƶ������֮��ľ��롣
	double min_dist = 0, max_dist = 0;//�������

	for (int i = 0; i < descriptors_1.rows; ++i)//����
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	printf("Max dist: %f\n", max_dist);
	printf("Min dist: %f\n", min_dist);

	//���岽��������С���룬��ƥ������ɸѡ��
	//��������֮��ľ������������min_dist������Ϊƥ��������������
	//������ʱ��С����ǳ�С������������0�ˣ����������ͻᵼ��min_dist��2*min_dist֮��û�м���ƥ�䡣
	// ���ԣ���2*min_distС��30��ʱ�򣬾�ȡ30������ֵ��С��30���ɣ�����2*min_dist���ֵ��
	std::vector<DMatch> good_matches;
	for (int j = 0; j < descriptors_1.rows; ++j)
	{
		if (matches[j].distance <= max(2 * min_dist, 30.0))
			good_matches.push_back(matches[j]);
	}

	//������������ƥ����

	Mat img_match;//����ƥ���ͼ
	//���￴һ��drawMatches()ԭ�Ͳ��������÷����ǣ�ͼ1��ͼ1�ؼ��㣬ͼ2��ͼ2�ؼ��㣬ƥ�����飬�н�ͼ�񣬺������Ĭ��ֵ
	/*
	CV_EXPORTS_W void drawMatches( InputArray img1,
								   const std::vector<KeyPoint>& keypoints1,
								   InputArray img2,
								   const std::vector<KeyPoint>& keypoints2,
								   const std::vector<DMatch>& matches1to2,
								   InputOutputArray outImg,
								   const Scalar& matchColor=Scalar::all(-1),
								   const Scalar& singlePointColor=Scalar::all(-1),
								   const std::vector<char>& matchesMask=std::vector<char>(),
								   int flags=DrawMatchesFlags::DEFAULT );
	*/

	drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_match);
	imshow("����ƥ����", img_match);

	Mat img_goodmatch;//ɸѡ���ƥ���ͼ
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);
	imshow("ɸѡ���ƥ����", img_goodmatch);

	waitKey(0);

	return 0;
}