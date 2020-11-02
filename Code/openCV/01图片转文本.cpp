#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string.h>
#include <fstream>

using namespace std;
using namespace cv;

void showImage(const char *winName, InputArray imgMat, int x, int y);
void outToFile(const char *fileName, const string content);

//ASCII字符是用来形容每个像素点的颜色深浅，从视觉效果(灰度)来看，字符的越复杂越能形容深色
const char codeLib[] = "@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

//图片输入输出
const char *imgFileName = "test.jpg";
const char *outFileName = "test.txt";

int main() {
    cout << strlen(codeLib) << " : " << codeLib << endl;
    Mat srcImg = imread(imgFileName);
    Mat grayImg;
    cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);

    string str;

    for(int y = 0; y < grayImg.rows; y++) {
        for (int x = 0; x < grayImg.cols; x++) {
            int grayVal = (int)grayImg.at<uchar>(y, x);
//            cout << grayVal << endl;
            int index = 69.0 / 255.0 * grayVal;
            str += codeLib[index];
        }
        str += "\r\n";
    }

    cout << str << endl;
    outToFile(outFileName, str);
    showImage("src", srcImg, 0, 0);
    showImage("gray", grayImg, 100, 100);
    waitKey(0);
    return 0;
}

//显示图片
void showImage(const char *winName, InputArray imgMat, int x, int y){
    namedWindow(winName, WINDOW_AUTOSIZE);
    moveWindow(winName![test.jpg](https://upload-images.jianshu.io/upload_images/5652117-67ba56d0f67ed1f4.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
, x, y);
    imshow(winName, imgMat);
}

//将字符串写入文件
void outToFile(const char *fileName, const string content){
    ofstream outStream;
    outStream.open(fileName);
    outStream << content << endl;
    outStream.close();
}