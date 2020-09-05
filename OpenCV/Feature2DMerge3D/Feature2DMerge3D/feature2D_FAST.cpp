
/**
* ����: ʹ��FAST������������
* ��ͺ���: FAST������FastFeatureDetector��
*/
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/features2d/features2d.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img_color = imread("feature.png");//ͼƬ·����.cpp�ļ���һ�𣬻��߾���·��
	Mat img;
	if (img_color.empty()) {
		printf("ͼƬ����ʧ�ܣ�����");
	}
	imshow("color", img_color);
	cvtColor(img_color, img, CV_BGR2GRAY);
	imshow("Grey", img);

	vector<KeyPoint> keypoints;
	Ptr<FastFeatureDetector> fast = FastFeatureDetector::create(20);
	fast->detect(img, keypoints);

	//-- ����������
	Mat img_keypoints;
	drawKeypoints(img, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//-- ��ʾ������
	imshow("Keypoints", img_keypoints);
	imwrite("fast_detection_result.png", img_keypoints);

	waitKey(0);
	return 0;
}