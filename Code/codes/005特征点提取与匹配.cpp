#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"  
#include "opencv2/features2d/features2d.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include  "opencv2/legacy/legacy.hpp" // 暴力匹配的头文件
#include  "opencv2/nonfree/nonfree.hpp"
#include <iostream>  
#include <vector> 

#include "cv_import_static_lib.h"

using namespace std;
using namespace cv;

void main(){


    Mat img_1 = imread("E:\\3Dtestdata\\3.jpg");
    Mat img_2 = imread("E:\\3Dtestdata\\4.jpg");
    if (!img_1.data || !img_2.data)
    {
        cout << "error reading images " << endl;
        return ;
    }

    vector<KeyPoint> keyPoints_1, keyPoints_2;
    Mat descriptors_1, descriptors_2;

    /*-----------------SIFT featrue Point----------------
    SIFT sift;
    sift(img_1, Mat(), keyPoints_1, descriptors_1);
    sift(img_2, Mat(), keyPoints_2, descriptors_2);
    */

    /*-----------------SURF featrue Point----------------
    SURF surf;
    surf(img_1, Mat(), keyPoints_1, descriptors_1);
    surf(img_2, Mat(), keyPoints_2, descriptors_2); 
    //SurfDescriptorExtractor extrator;           // another surf sift operation 
    //extrator.compute(img_1, keyPoints_1, descriptors_1);
    //extrator.compute(img_2, keyPoints_2, descriptors_2);
    */

    //-----------------ORB featrue Point----------------
    ORB orb;   // float Feature, can not use FlannBase Match.
    orb(img_1, Mat(), keyPoints_1, descriptors_1);
    orb(img_2, Mat(), keyPoints_2, descriptors_2);


    /*-----------------ORB featrue Point----------------
    MSER mesr;
     */

    /*-----------------FAST featrue Point----------------
    FastFeatureDetector fast1(100);   // 检测的阈值为40  
    FastFeatureDetector fast2(100);

    fast1.detect(img_1, keyPoints_1);
    fast2.detect(img_2, keyPoints_2);
    //SurfDescriptorExtractor extrator;           // another surf sift operation 
    //extrator.compute(img_1, keyPoints_1, descriptors_1);
    //extrator.compute(img_2, keyPoints_2, descriptors_2);

    OrbDescriptorExtractor extrator;
    extrator.compute(img_1, keyPoints_1, descriptors_1);
    extrator.compute(img_2, keyPoints_2, descriptors_2);
    */


    BruteForceMatcher<HammingLUT> matcher;// orb 等float型的

    //FlannBasedMatcher matcher;   // 只能 对uchar的点进行匹配

    vector< DMatch > matches;

    matcher.match(descriptors_1, descriptors_2, matches);

    double max_dist = 0; double min_dist = 100;
    //-- Quick calculation of max and min distances between keypoints  
    for (int i = 0; i < descriptors_1.rows; i++)
    {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }
    cout<<"-- Max dist :"<< max_dist<<endl;
    cout<<"-- Min dist :"<< min_dist<<endl;

    //-- Draw only "good" matches (i.e. whose distance is less than 0.6*max_dist )  
    //-- PS.- radiusMatch can also be used here.  
    vector< DMatch > good_matches;
    for (int i = 0; i < descriptors_1.rows; i++)
    {
        if (matches[i].distance < 0.6*max_dist)
        {
            good_matches.push_back(matches[i]);
        }
    }


    // vector<KeyPoint> m_LeftKey;
    // vector<KeyPoint> m_RightKey;
    // vector<DMatch> m_Matches;
    // 以上三个变量已经被计算出来，分别是提取的关键点及其匹配，下面直接计算F

    // 分配空间
    int ptCount = (int)matches.size();
    Mat p1(ptCount, 2, CV_32F);
    Mat p2(ptCount, 2, CV_32F);

    // 把Keypoint转换为Mat
    Point2f pt;
    for (int i = 0; i<ptCount; i++)
    {
        pt = keyPoints_1[matches[i].queryIdx].pt;
        p1.at<float>(i, 0) = pt.x;
        p1.at<float>(i, 1) = pt.y;

        pt = keyPoints_2[matches[i].trainIdx].pt;
        p2.at<float>(i, 0) = pt.x;
        p2.at<float>(i, 1) = pt.y;
    }


    // 用RANSAC方法计算 基本矩阵F
    Mat m_Fundamental;
    vector<uchar> m_RANSACStatus;

    m_Fundamental = findFundamentalMat(p1, p2, m_RANSACStatus, FM_RANSAC);//?????????????????

    // 计算野点个数
    int OutlinerCount = 0;
    for (int i = 0; i<ptCount; i++)
    {
        if (m_RANSACStatus[i] == 0) // 状态为0表示野点
        {
            OutlinerCount++;
        }
    }

    // 计算内点
    vector<Point2f> m_LeftInlier;
    vector<Point2f> m_RightInlier;
    vector<DMatch> m_InlierMatches;
    // 上面三个变量用于保存内点和匹配关系
    int InlinerCount = ptCount - OutlinerCount;
    m_InlierMatches.resize(InlinerCount);
    m_LeftInlier.resize(InlinerCount);
    m_RightInlier.resize(InlinerCount);
    InlinerCount = 0;
    for (int i = 0; i<ptCount; i++)
    {
        if (m_RANSACStatus[i] != 0)
        {
            m_LeftInlier[InlinerCount].x = p1.at<float>(i, 0);
            m_LeftInlier[InlinerCount].y = p1.at<float>(i, 1);
            m_RightInlier[InlinerCount].x = p2.at<float>(i, 0);
            m_RightInlier[InlinerCount].y = p2.at<float>(i, 1);
            m_InlierMatches[InlinerCount].queryIdx = InlinerCount;
            m_InlierMatches[InlinerCount].trainIdx = InlinerCount;
            InlinerCount++;
        }
    }

    // 把内点转换为drawMatches可以使用的格式
    vector<KeyPoint> key1(InlinerCount);
    vector<KeyPoint> key2(InlinerCount);
    KeyPoint::convert(m_LeftInlier, key1);
    KeyPoint::convert(m_RightInlier, key2);

    // 显示计算F过后的内点匹配
     //Mat m_matLeftImage;
     //Mat m_matRightImage;
    // 以上两个变量保存的是左右两幅图像
    Mat OutImage;
    drawMatches(img_1, key1, img_2, key2, m_InlierMatches, OutImage);

    //stereoRectifyUncalibrated();

    Mat img_matches;
    drawMatches(img_1, keyPoints_1, img_2, keyPoints_2,
    good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
    vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    imwrite("FASTResult.jpg", img_matches);
    imshow("Match", img_matches);

    imwrite("FmatrixResult.jpg", OutImage);
    imshow("Match2", OutImage);
    waitKey(0);

    return;
}