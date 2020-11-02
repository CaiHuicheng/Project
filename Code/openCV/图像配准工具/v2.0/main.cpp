#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"  
#include <Windows.h>
#include <iostream>
#include "NewWindows.h"

using namespace std;
using namespace cv;

void CreateWindows(char* s, char* pic);
void CreateWindows2(char* s, char* pic);

vector<Point2f> imagePoints1, imagePoints2;  //记录匹配点


DWORD WINAPI ThreadFun1(LPVOID pM)
{
    NewWindow ref_obj("基准", "ref.jpg");
    ref_obj.CreateWindows();
    imagePoints1 = ref_obj.imagePoints;
    return 0;
}

DWORD WINAPI ThreadFun2(LPVOID pM)
{
    NewWindow src_obj("待变换", "src.jpg");
    src_obj.CreateWindows();
    imagePoints2 = src_obj.imagePoints;
    return 0;
}

int HandSlectPoint()
{

    Mat tsrc1 = imread("ref.jpg");  //基准图
    Mat tsrc2 = imread("src.jpg");


    while (1)
    {
#if 1
        imagePoints1.clear();
        imagePoints2.clear();

        HANDLE handle1 = CreateThread(NULL, 0, ThreadFun1, NULL, 0, NULL);  //创建线程

        HANDLE handle2 = CreateThread(NULL, 0, ThreadFun2, NULL, 0, NULL);

        printf("往下执行？\n");

        //先拥塞住，点选完再进行计算变换矩阵
        string s;
        cin >> s;

        Mat homo = findHomography(imagePoints2, imagePoints1, CV_RANSAC);

        Mat imageTransform1;
        warpPerspective(tsrc2, imageTransform1, homo, Size(tsrc1.cols, tsrc1.rows));
        imwrite("trans.jpg", imageTransform1); //把配准后结果存起来

        CloseHandle(handle1);//销毁线程1  
        CloseHandle(handle2);//销毁线程1  

#endif
        printf("是否结束？\n");

        //判断是否结束，如果点选得不好，就再来一次
        string str;
        cin >> str;
        if (str == "yes")
            break;

    }

    return 0;
}

int main()
{
    HandSlectPoint();

    return 0;
}