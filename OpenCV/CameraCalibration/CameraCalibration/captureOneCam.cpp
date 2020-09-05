#include <opencv2\imgcodecs.hpp>
#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
/*
   单相机拍照程序
*/
int process(VideoCapture& capture)
{
	int n = 0;//保存相片数
	char filename[200];//保存的图片路径名
	string windowName = "camera_0";//窗口名
	cout << "Enter the space bar to save the picture.\n";
	Mat frame;
	for (;;)//无限循环，读取没一帧的数据
	{
		capture >> frame;//将捕获的一帧输入到Mat矩阵中
		if (frame.empty())//如果获得的一帧为空则返回，重新抓取
			break;
		imshow(windowName, frame);//显示相机抓取的窗口
		char key = (char)waitKey(30);//每显示一帧数据的时候停30ms，检测是否按下按键
		switch (key) 
		{
		case 'q':
		case 'Q':
		case 27: // escape
			return 0;
		case ' '://空格键，保存信息
			sprintf_s(filename, "0%.1d.png", n++);
			imwrite(filename, frame);//将抓拍的图片，保存
			cout << "Saved " << filename << endl;
			break;
		default:
			break;
		}
	}
	return 0;
}

int main()
{
	VideoCapture capture(0);//创建相机的视频抓取，0号设备，一般为笔记本的摄像机
	if (!capture.isOpened())//判断相机是否开启
	{
		cerr << "No camera detected.\n";
		return 1;
	}
	return process(capture);
}
