#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	cv::VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
		return 0;
	/// 从摄像头读取图像
	cv::Mat src;
	for (;;)
	{
		cap >> src;
		//imshow("1", src);
		Mat distortion = src.clone();
		//imshow("2", distortion);
		Mat camera_matrix = Mat(3, 3, CV_32FC1);
		Mat distortion_coefficients;


		//导入相机内参和畸变系数矩阵
		FileStorage file_storage("E:/OPEN_TEST/Project_cup/out_camera_data.xml", FileStorage::READ);
		file_storage["camera_matrix"] >> camera_matrix;
		cout << camera_matrix << endl;
		file_storage["distortion_coefficients"] >> distortion_coefficients;
		cout << distortion_coefficients << endl;
		file_storage.release();

		//矫正
		undistort(src, distortion, camera_matrix, distortion_coefficients);
		if (src.empty()) break;
		if (cv::waitKey(15) >= 0) break;  //这一句一定要有，不然会死循环，不显示图像
		imshow("img", src);
		imshow("undistort", distortion);
	}
	waitKey(0);
	cap.release();
	cv::destroyAllWindows();
}