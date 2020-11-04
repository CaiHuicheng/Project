/**************************************************
���ܣ�����ͼ��ֱ��ͼ��ˮƽ����ʹ�ֱ�����ͶӰ
���룺
	srcImg��Դͼ��
�����
	horiProj: ˮƽ�����ͶӰ�����1 * height�����ָ�룬����ǰ�ǵó�ʼ��
	vertProj����ֱ�����ͶӰ�����1 * width�����ָ�룬����ǰ�ǵó�ʼ��
**************************************************/

#include<opencv2/imgproc.hpp>

void histProject(IplImage * srcImg, int* horiProj, int* vertProj)
{
	// �����õ��Ĳ���
	int i, j;
	uchar* ptr = NULL;					// ָ��ͼ��ǰ���׵�ַ��ָ��
	uchar* temp = NULL;
	int HEIGHT = srcImg->height;
	int WIDTH = srcImg->width;

	
	for(i = 0; i < HEIGHT; i ++){
		ptr = (uchar*) (srcImg->imageData + i * srcImg->widthStep);
		for(j = 0; j < WIDTH; j ++){
			temp = ptr + j;				// ���ټ�����
			*(horiProj + i) += *temp;	// ����ˮƽ�����ͶӰ
			*(vertProj + j) += *temp;	// ���㴹ֱ�����ͶӰ
		}
	}

}