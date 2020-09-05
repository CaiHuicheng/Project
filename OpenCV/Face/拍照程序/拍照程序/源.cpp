#include <opencv2\opencv.hpp>
#include <vector>
#include <iostream>
#include<stdio.h>
//#include <stdio.h>
//#include <cv.h>  
using namespace std;
using namespace cv;
int main()
{
	CascadeClassifier cascada;
	cascada.load("haarcascade_frontalface_alt2.xml");
	VideoCapture cap(0);
	Mat frame, myFace;
	int pic_num = 1;
	while (1) {
		//摄像头读图像
		cap >> frame;
		vector<Rect> faces;//vector容器存检测到的faces
		Mat frame_gray;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);//转灰度化，减少运算
		cascada.detectMultiScale(frame_gray, faces, 1.1, 4, CV_HAAR_DO_ROUGH_SEARCH, Size(70, 70));
		printf("检测到人脸个数：%d\n", faces.size());
		for (int i = 0; i < faces.size(); i++)
		{
			rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
		}
		//当只有一个人脸时，开始按空格拍照
		if (faces.size() == 1)
		{
			if (32 == waitKey(20)) {
				Mat faceROI = frame_gray(faces[0]);//在灰度图中将圈出的脸所在区域裁剪出
			   //cout << faces[0].x << endl;//测试下face[0].x
				resize(faceROI, myFace, Size(92, 112));//将兴趣域size为92*112
				putText(frame, to_string(pic_num), faces[0].tl(), 3, 1.2, (0, 0, 225), 2, 0);//在 faces[0].tl()的左上角上面写序号
				string filename = to_string(pic_num) + ".bmp"; //存放在当前项目文件夹以1-10.jpg/pgm 命名，format就是转为字符串
				cout << filename << endl;
				imwrite(filename, myFace);//存在当前目录下
				imshow(filename, myFace);//显示下size后的脸
				cout << "人脸图片：" << filename << endl;
				waitKey(500);//等待500us
				destroyWindow(filename);//:销毁指定的窗口
				pic_num++;//序号加1
				if (pic_num == 11)
				{
					return 0;//当序号为11时退出循环
				}
			}
				
		}
		int c = waitKey(10);
		if ((char)c == 27) { break; } //10us内输入esc则退出循环
		imshow("frame", frame);//显示视频流
		waitKey(100);//等待100us
	}
	return 0;
}