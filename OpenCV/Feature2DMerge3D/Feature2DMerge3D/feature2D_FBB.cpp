#include <iostream>
#include <windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 

using namespace std;
using namespace cv;

int main ( int argc, char** argv )
{
    /*if ( argc != 3 )
    {
        cout<<"usage: feature_extraction img1 img2"<<endl;
        return 1;
    }*/
    //��ȡͼ��
	//Mat img_1 = imread("1.png");
	//Mat img_2 = imread("2.png");
	Mat img_color1 = imread("1.png");//ͼƬ·����.cpp�ļ���һ�𣬻��߾���·��
	Mat img_color2 = imread("2.png");//ͼƬ·����.cpp�ļ���һ�𣬻��߾���·��
	Mat img_1;
	Mat img_2;
	cvtColor(img_color1, img_1, CV_BGR2GRAY);
	cvtColor(img_color2, img_2, CV_BGR2GRAY);
	imshow("Grey1", img_1);
	imshow("Grey2", img_2);

    //��ʼ��
    std::vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher  = DescriptorMatcher::create ( "BruteForce-Hamming" );

    //��� Oriented FAST �ǵ�λ��
    detector->detect ( img_1,keypoints_1 );
    detector->detect ( img_2,keypoints_2 );

    //���ݽǵ�λ�ü��� BRIEF ������
    descriptor->compute ( img_1, keypoints_1, descriptors_1 );
    descriptor->compute ( img_2, keypoints_2, descriptors_2 );

    Mat outimg1;
    drawKeypoints( img_1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    imshow("ORB������",outimg1);

    //������ͼ���е�BRIEF�����ӽ���ƥ�䣬ʹ�� Hamming ����
    vector<DMatch> matches;
    matcher->match ( descriptors_1, descriptors_2, matches );

    //ƥ����ɸѡ
    double min_dist=10000, max_dist=0;

    //�ҳ�����ƥ��֮�����С�����������, ���������Ƶĺ�����Ƶ������֮��ľ���
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        double dist = matches[i].distance;
        if ( dist < min_dist ) min_dist = dist;
        if ( dist > max_dist ) max_dist = dist;
    }
    
    // �������ֵ�д��
    min_dist = min_element( matches.begin(), matches.end(), [](const DMatch& m1, const DMatch& m2) {return m1.distance<m2.distance;} )->distance;
    max_dist = max_element( matches.begin(), matches.end(), [](const DMatch& m1, const DMatch& m2) {return m1.distance<m2.distance;} )->distance;

    printf ( "-- Max dist : %f \n", max_dist );
    printf ( "-- Min dist : %f \n", min_dist );

    //��������֮��ľ��������������С����ʱ,����Ϊƥ������.����ʱ����С�����ǳ�С,����һ������ֵ30��Ϊ����.
    std::vector< DMatch > good_matches;
    for ( int i = 0; i < descriptors_1.rows; i++ )
    {
        if ( matches[i].distance <= max ( 2*min_dist, 30.0 ) )
        {
            good_matches.push_back ( matches[i] );
        }
    }

    //����ƥ����
    Mat img_match;
    Mat img_goodmatch;
    drawMatches ( img_1, keypoints_1, img_2, keypoints_2, matches, img_match );
    drawMatches ( img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch );
    imshow ( "����ƥ����", img_match );
    imshow ( "�Ż���ƥ����", img_goodmatch );
    waitKey(0);

    return 0;
}


