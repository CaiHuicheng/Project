/*
���̴���˼·��
��ͨ��Kmeansѵ����Ŀ��Ϊ�˵õ��������ص�һ����ǣ����˾���û�������Ҫ���Լ۱�̫���ˣ�
���������Ǹ�֤���յ�ԭͼ����һ�������õ�������ǰ����һ����0��255���ķֿ����ܹ������Ϊmask
�������mask����һ��ɧ������Ŀ����Ϊ�˺�����𻯱�Ե���õ����Ӿ�ȷ��Ч����
�𻯱�Ե�м���˼·���Ƚ������ֵģ���
����3X3���ں�ȥ��һ���߽����أ������ø�˹ģ���õ��ݶȱ�Ե���õ����֮��������һ�������У�
������ݶȵĸߵ͸��費ͬ�ı߽����أ�����Ȩ�صõ��߽�ֵ
���Ĳ����Ǹ���mask��ֵ���費ͬ��ֵ
�����0��Ϊ��������
�����255��Ϊ֤���յ�ǰ������
������ֵ�͸����ݶȵĴ�С��Ȩ�ؽ������¸�ֵ
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat labels;
Mat centers;

Mat mat_to_samples(Mat &image);
int main(int argc, char** argv) {
	Mat src = imread("0.png");
	if (src.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	// ��װ����
	int w1 = src.cols;
	int h = src.rows;
	int samplecount = w1*h;
	int dims = src.channels();
	Mat points(samplecount, dims, CV_32F, Scalar(10));

	int index1 = 0;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w1; col++) {
			index1 = row*w1 + col;
			Vec3b bgr = src.at<Vec3b>(row, col);
			points.at<float>(index1, 0) = static_cast<int>(bgr[0]);
			points.at<float>(index1, 1) = static_cast<int>(bgr[1]);
			points.at<float>(index1, 2) = static_cast<int>(bgr[2]);
		}
	}

	// ����KMeans
	int numCluster = 4;

	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(points, numCluster, labels, criteria, 3, KMEANS_PP_CENTERS, centers);

	//�Ҿ���û�б�Ҫ��������Ͼ�����ļ�ֵֻ��Ϊ���ҵ������ı�ǰ��ˣ�
	//����ô���ʱ�任ȡ������ɱ�̫�������̫����



	// ȥ����+��������
	Mat mask = Mat::zeros(src.size(), CV_8UC1);
	int index = src.rows * 2 + 2;
	int cindex = labels.at<int>(index, 0);
	int height = src.rows;
	int width = src.cols;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			index = row*width + col;
			int label = labels.at<int>(index, 0);
			if (label == cindex) {
				// ����
				//dst.at<Vec3b>(row, col)[0] = 0;
				//dst.at<Vec3b>(row, col)[1] = 0;
				//dst.at<Vec3b>(row, col)[2] = 0;
				mask.at<uchar>(row, col) = 0;
			}
			else {
				mask.at<uchar>(row, col) = 255;
			}
		}
	}
	//imshow("mask", mask);

	// ��ʴ + ��˹ģ��
	Mat mask_morph, mask_blur;
	Mat k = getStructuringElement(MORPH_RECT, Size(7, 7), Point(-1, -1));
	erode(mask, mask_morph, k);					//��ʴ�������ͼ���ɫ�߽�����һ���߽����أ���ȫ���������߽�
												//imshow("erode-mask", mask);
												//����һ��ɧ��������ǰ��֪����ԭ��3X3���ں�ȥ�����ǹ����ϵ�һ���߽����أ�5X5ȥ�����������߽����أ����������~
	GaussianBlur(mask_morph, mask_blur, Size(3, 3), 0, 0);
	//imshow("Blur Mask", mask);				//ʹ�ñ߽��˹ģ����ԭ����0��255���0��64��191��255

	/*
	ΪʲôҪ�����ⲽ�����أ�
	1.�𻯱߽磬��ͨ����̬ѧ��ʴ��Ϊ���������߽��ڡ���ʴ + ��˹ģ���� ������������Ե�����ر��ֲ���
	��˹ģ����ԭ�����ڽ�ԭ����0��255�����ر��0��64��191��255��ʹ�ñ߽粻�ᷢ��ͻ�䣬�������𻯵�����
	*/


	// ͨ�����
	RNG rng(12345);
	Vec3b color;
	color[0] = 217;//rng.uniform(0, 255);
	color[1] = 60;// rng.uniform(0, 255);
	color[2] = 160;// rng.uniform(0, 255);
	Mat result(src.size(), src.type());

	double w = 0.0;
	int b = 0, g = 0, r = 0;
	int b1 = 0, g1 = 0, r1 = 0;
	int b2 = 0, g2 = 0, r2 = 0;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int m = mask_blur.at<uchar>(row, col);
			if (m == 255) {
				result.at<Vec3b>(row, col) = src.at<Vec3b>(row, col); // ǰ��
			}
			else if (m == 0) {
				result.at<Vec3b>(row, col) = color; // ����
			}
			else {
				w = m / 255.0;
				b1 = src.at<Vec3b>(row, col)[0];
				g1 = src.at<Vec3b>(row, col)[1];
				r1 = src.at<Vec3b>(row, col)[2];

				b2 = color[0];
				g2 = color[1];
				r2 = color[2];

				b = b1*w + b2*(1.0 - w);
				g = g1*w + g2*(1.0 - w);
				r = r1*w + r2*(1.0 - w);

				result.at<Vec3b>(row, col)[0] = b;
				result.at<Vec3b>(row, col)[1] = g;
				result.at<Vec3b>(row, col)[2] = r;
			}
		}
	}
	imshow("�����滻", result);

	waitKey(0);
	return 0;
}