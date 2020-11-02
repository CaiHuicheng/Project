#include<opencv2\opencv.hpp>   
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	Mat img = imread("src1.jpg");

	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION); //PNG格式图片的压缩级别  
	compression_params.push_back(9);  //这里设置保存的图像质量级别

	imwrite("test3.png", img,compression_params);

	return 0;
}
