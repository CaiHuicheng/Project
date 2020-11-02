#include <opencv2\opencv.hpp>
#include <iostream>
#include <math.h>
using namespace cv;
int main(int argc, char** argv)
{
	 Mat src = imread("test1.jpg");
	 namedWindow("ShowImage1", CV_WINDOW_AUTOSIZE);
	 imshow("ShowImage1", src);
	 namedWindow("ShowImage2", CV_WINDOW_AUTOSIZE);
	 Mat output_image;
	 cvtColor(src, output_image, CV_RGB2HLS);
	 imshow("ShowImage2", output_image);
	 imwrite("test.tif", output_image);
	 waitKey(0);
	 return 0;
}