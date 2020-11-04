/********************************************************
���ܣ���ͼ��������Ե����㣬ʵ��ͼ����ǿ
���룺
		IplImage* srcImg: Դ�Ҷ�ͼ��
		float a����ϵ��a
�����
		IplImage* dstImg������������Ա任���ͼ��
********************************************************/

#include<opencv2\highgui\highgui.hpp>
#include<opencv2/imgproc.hpp>

void nonlineTrans(IplImage* srcImg, IplImage* dstImg, float a)
{
	int i, j;
	uchar* ptr = NULL;					// ָ��ͼ��ǰ���׵�ַ��ָ��
	uchar* pixel = NULL;				// ָ�����ص��ָ��
	float temp;

	dstImg = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U, 1);
	cvCopy(srcImg, dstImg, NULL);
	int HEIGHT = dstImg->height;
	int WIDTH = dstImg->width;
	
	for(i = 0; i < HEIGHT; i ++){
		ptr = (uchar*) (srcImg->imageData + i * srcImg->widthStep);
		for(j = 0; j < WIDTH; j ++){
			pixel = ptr + j;

			// �����Ա任
			temp = *pixel + (a * (*pixel) * (255 - *pixel)) / 255;

			// �жϷ�Χ
			if ( temp > 255 )
				*pixel = 255;
			else if (temp < 0)
				*pixel = 0;
			else
				*pixel = (uchar)(temp + 0.5);// ��������
		}
	}
}