#include<opencv2\opencv.hpp>   
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;


int main(int argc, char** argv)
{
	Mat img = imread("src1.jpg");

	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择jpeg
	compression_params.push_back(100); //在这个填入你要的图片质量

	imwrite("test2.jpg", img, compression_params);

	return 0;
}