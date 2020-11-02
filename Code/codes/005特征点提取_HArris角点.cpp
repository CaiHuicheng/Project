#include "highgui/highgui.hpp"    
#include "opencv2/nonfree/nonfree.hpp"    
#include "opencv2/legacy/legacy.hpp"   
#include <iostream>  

using namespace cv;
using namespace std;


int main()
{

    Mat image01 = imread("1.jpg", 1);
    Mat image02 = imread("2.jpg", 1);
    imshow("p2", image01);
    imshow("p1", image02);

    //灰度图转换  
    Mat image1, image2;
    cvtColor(image01, image1, CV_RGB2GRAY);
    cvtColor(image02, image2, CV_RGB2GRAY);


    //提取特征点    
    GoodFeaturesToTrackDetector Detector(500);  //最大点数,值越大，点越多
    vector<KeyPoint> keyPoint1, keyPoint2;
    Detector.detect(image1, keyPoint1);
    Detector.detect(image2, keyPoint2);

    //特征点描述，为下边的特征点匹配做准备    
    SiftDescriptorExtractor  Descriptor;
    Mat imageDesc1, imageDesc2;
    Descriptor.compute(image1, keyPoint1, imageDesc1);
    Descriptor.compute(image2, keyPoint2, imageDesc2);

    BruteForceMatcher< L2<float> > matcher;   
    vector<vector<DMatch> > matchePoints;
    vector<DMatch> GoodMatchePoints;

    vector<Mat> train_desc(1, imageDesc1);
    matcher.add(train_desc);
    matcher.train();

    matcher.knnMatch(imageDesc2, matchePoints, 2);
    cout << "total match points: " << matchePoints.size() << endl;

    // Lowe's algorithm,获取优秀匹配点
    for (int i = 0; i < matchePoints.size(); i++)
    {
        if (matchePoints[i][0].distance < 0.6 * matchePoints[i][1].distance)
        {
            GoodMatchePoints.push_back(matchePoints[i][0]);
        }
    }

    Mat first_match;
    drawMatches(image02, keyPoint2, image01, keyPoint1, GoodMatchePoints, first_match);
    imshow("first_match ", first_match);
    imwrite("first_match.jpg", first_match);
    waitKey();
    return 0;
}