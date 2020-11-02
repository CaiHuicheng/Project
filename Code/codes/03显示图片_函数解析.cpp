#include <iostream>
#include "opencv.hpp"
using namespace cv;

//  Mat imread(const string& filename,flags = 1)
//  filename:载入图片的路径，支持载入的图片的格式：bmp,dib,jpeg,jpg,jpe,jp2,png,pbm,pgm,ppm,sr,ras,tiff,tif
//  flags:  
//      flags>0 返回一个3通道的彩色图像；
//      flags=0 返回灰色图像；
//      flags<0 返回包含Alpha通道的图像

//  void imshow(const string& winname, InputArray mat)
//  winname:窗口名称
//  mat:需要显示的图像

//  void namedWindow(cosnt string& winname, int flags = WINDOW_AUTOSIZE)
//  winname:创建窗口的名称
//  flags:
//      WINDOW_NORMAL:用户可以缩放窗口
//      WINDOW_AUTOSIZE：窗口适应图像
//      WINDOW_OPENGL：窗口创建之初opengl

//  bool imwrite( const String& filename, InputArray img, const std::vector<int>& params = std::vector<int>())
//  filename:输出的文件名
//  img:用于输出的Mat数据
//  params：特定格式保存的参数编码，一般不需要填写

//  int waitKey(int delay = 0)
//  delay：等待delay秒关闭窗口

int main()
{
    Mat srcImage = imread("1.jpg");     //载入图像
    namedWindow("原图", WINDOW_NORMAL);   //创建窗口
    imshow("原图", srcImage);         //显示原图
    imwrite("output.jpg", srcImage);    //写入文件
    waitKey();                          //waitKey()与waitKey(0)，都代表无限等待窗口显示，直到任何按键按下

    return 0;
}