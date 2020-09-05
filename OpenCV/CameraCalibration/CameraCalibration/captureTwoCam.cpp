#include <opencv2\imgcodecs.hpp>
#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
/*
   双目相机拍照程序
*/
int process(VideoCapture capture[])
{
	int n = 0;//保存相片数
	char filename[200];//保存的图片路径名
	string windowName = "TWOCam";//窗口名
	cout << "Enter the space bar to save the picture.\n";
	Mat frame[2];//定义抓取的帧数据存储矩阵，两个摄像头的
	for (;;)//无限循环，读取没一帧的数据
	{
		capture[0] >> frame[0];//摄像头0将捕获的一帧输入到Mat[0]矩阵中
		waitKey(20);
		capture[1] >> frame[1];//摄像头1将捕获的一帧输入到Mat[1]矩阵中
		if (frame[0].empty()|| frame[1].empty())//如果获得的一帧为空则返回，重新抓取
			break;
		transpose(frame[0], frame[0]);
		//flip(frame[0], frame[0], 1);
		imshow("Video0", frame[0]);
		//flip(frame[1],);
		transpose(frame[1], frame[1]);
		//flip(frame[1], frame[1], -1);//反转矩阵，摄像头方向问题，借助flip调整
		imshow("Video1", frame[1]);
		char key = (char)waitKey(70);//每显示一帧数据的时候停70ms，检测是否按下按键
		switch (key)
		{
		case 'q':
		case 'Q':
		case 27: // escape
			return 0;
		case ' '://空格键，保存信息
			sprintf(filename, "imageLeft%.1d.jpg", n);
			imwrite(filename, frame[0]);
			cout << "Saved " << filename << endl;
			sprintf(filename, "imageRight%.1d.jpg", n++);
			imwrite(filename, frame[1]);
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
	VideoCapture capture[2];
	capture[0].open(0);
	capture[1].open(1);
	if (!capture[0].isOpened())
	{
		cerr << "Failed to open the video device [0].\n";
		return 1;
	}
	if (!capture[1].isOpened())
	{
		cerr << "Failed to open the video device [1].\n";
		return 1;
	}
	return process(capture);
}
