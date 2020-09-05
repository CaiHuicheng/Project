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
		cascada.detectMultiScale(frame_gray, faces, 1.1, 4, CV_HAAR_DO_ROUGH_SEARCH, Size(70, 70), Size(1000, 1000));
		printf("检测到人脸个数：%d\n", faces.size());
		//1.frame_gray表示的是要检测的输入图像 2.faces表示检测到的人脸目标序列,3. 1.1表示每次图像尺寸减小的比例
		//4. 4表示每一个目标至少要被检测到3次才算是真的目标(因为周围的像素和不同的窗口大小都可以检测到人脸表示每一个目标至少要被检测到3次才算是真的目标(因为周围的像素和不同的窗口大小都可以检测到人脸
		/*5.flags–要么使用默认值，要么使用CV_HAAR_DO_CANNY_PRUNING，
		函数将会使用Canny边缘检测来排除边缘过多或过少的区域，
		因为这些区域通常不会是人脸所在区域；opencv3 以后都不用这个参数了*/
		//6. Size(100, 100)为目标的最小尺寸 一般为30*30 是最小的了 也够了
		//7. Size(500, 500)为目标的最大尺寸 其实可以不用这个，opencv会自动去找这个最大尺寸
		//适当调整5,6,7两个参数可以用来排除检测结果中的干扰项。
		//识别到的脸用矩形圈出
		for (int i = 0; i < faces.size(); i++)
		{
			rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
		}
		//当只有一个人脸时，开始拍照
		int key;
		if ((key = waitKey(5)) != -1) {
			if (faces.size() == 1 && key == ' ')
			{
				Mat faceROI = frame_gray(faces[0]);//在灰度图中将圈出的脸所在区域裁剪出
												   //cout << faces[0].x << endl;//测试下face[0].x
				resize(faceROI, myFace, Size(92, 112));//将兴趣域size为92*112
				putText(frame, to_string(pic_num), faces[0].tl(), 3, 1.2, (0, 0, 225), 2, 0);//在 faces[0].tl()的左上角上面写序号
				string filename = format("%d.jpg", pic_num); //存放在当前项目文件夹以1-10.jpg 命名，format就是转为字符串
				imwrite(filename, myFace);//存在当前目录下
				imshow(filename, myFace);//显示下size后的脸
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