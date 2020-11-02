#include "highgui/highgui.hpp"    
#include "opencv2/nonfree/nonfree.hpp"    
#include "opencv2/legacy/legacy.hpp"   
#include <iostream>  

using namespace cv;
using namespace std;


int main()
{
    Mat image01 = imread("2.jpg", 1);    //右图
    Mat image02 = imread("1.jpg", 1);    //左图
    namedWindow("p2", 0);
    namedWindow("p1", 0);
    imshow("p2", image01);
    imshow("p1", image02);

    //灰度图转换  
    Mat image1, image2;
    cvtColor(image01, image1, CV_RGB2GRAY);
    cvtColor(image02, image2, CV_RGB2GRAY);


    //提取特征点    
    SurfFeatureDetector surfDetector(800);  // 海塞矩阵阈值，在这里调整精度，值越大点越少，越精准 
    vector<KeyPoint> keyPoint1, keyPoint2;
    surfDetector.detect(image1, keyPoint1);
    surfDetector.detect(image2, keyPoint2);

    //特征点描述，为下边的特征点匹配做准备    
    SurfDescriptorExtractor SurfDescriptor;
    Mat imageDesc1, imageDesc2;
    SurfDescriptor.compute(image1, keyPoint1, imageDesc1);
    SurfDescriptor.compute(image2, keyPoint2, imageDesc2);

    //获得匹配特征点，并提取最优配对     
    FlannBasedMatcher matcher;
    vector<DMatch> matchePoints;

    matcher.match(imageDesc1, imageDesc2, matchePoints, Mat());
    cout << "total match points: " << matchePoints.size() << endl;


    Mat img_match;
    drawMatches(image01, keyPoint1, image02, keyPoint2, matchePoints, img_match);
    namedWindow("match", 0);
    imshow("match",img_match);
    imwrite("match.jpg", img_match);

    waitKey();
    return 0;
}