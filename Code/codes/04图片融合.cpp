#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
 
int trackBarValueCurrent = 0;//轨迹条当前值
int trackBarValueMax = 100;//轨迹条最大值
Mat img1, img2,img;
char *windowName = "图像融合";//窗口名称
char *trackBarName = "进度条";//进度条名称
 
void trackBarFun(int ,void*)
{
	float rate = (float)trackBarValueCurrent / trackBarValueMax;
	addWeighted(img1, rate, img2, 1 - rate, 0, img);
	imshow(windowName, img);
}
 
int main(int argc, char *argv[])
{
	img1 = imread("E\\codes\\image\\8.png");
	img2 = imread("E\\codes\\image\\9.png");
		
	if (img1.empty() || img2.empty())
	{
		cout << "图片读取错误" << endl;
		exit(1);
	}
	
	resize(img1, img1, Size(img2.cols, img2.rows));//将img1的图片大小变为与img2一样
	namedWindow(windowName);
	createTrackbar(trackBarName, windowName, &trackBarValueCurrent, trackBarValueMax, trackBarFun);
	trackBarFun(0,0);
	waitKey();
 
	return 0;
}
