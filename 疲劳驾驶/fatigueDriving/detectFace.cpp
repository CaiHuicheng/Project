/**************************************************
���ܣ����ͼƬ�е���������

���룺
	IplImage* srcImg,					// �Ҷ�ͼ��
	CvMemStorage* storage,				// �洢���ο���ڴ�����
	double scale_factor = 1.1,			// �������ڵı���ϵ��
	int min_neighbors = 3,				// ���ɼ��Ŀ������ھ��ε���С����
	int flags = 0,						// ������ʽ
	CvSize min_size = cvSize(20, 20)	// ��ⴰ�ڵ���С�ߴ�

���������	
	CvSeq* objects				// ��⵽�����ľ��ο�

˵����	1. ʶ���׼ȷ�ʺ��ٶȹؼ�����cvHaarDetectObject���������Ĳ����ĵ���
		2. ���ʵ�����������ڼ��Ч������ʱ���ɿ����Լ��Ѽ���������ͼƬȻ��ѵ��������
		3. ʵ������ƣ�ͼ�ʻ���ʱ����������λ��ͼƬ���������ռ������ܴ󣬿��Խ�min_size��scale_factor����һЩ���ӿ��ٶ�
		4. �ں�ֱ��ͼ���⻯
**************************************************/
#include "stdlib.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2/imgproc.hpp>
#include "opencv2/face.hpp"

extern CvSeq* objectsTemp;		// ����objects��ֵ��main����
void detectFace(
	IplImage* srcImg,					// �Ҷ�ͼ��
	CvSeq* objects,						// �����������⵽�����ľ��ο�
	CvMemStorage* storage,				// �洢���ο���ڴ�����
	double scale_factor = 1.1,			// �������ڵı���ϵ��
	int min_neighbors = 3,				// ���ɼ��Ŀ������ھ��ε���С����
	int flags = 0,						// ������ʽ
	CvSize min_size = cvSize(20, 20)	// ��ⴰ�ڵ���С�ߴ�
)
{
	// �����õ��Ĳ���
	const char* cascadeName = "haarcascade_frontalface_alt2.xml"; // ������������xml�ļ���

	// ��ȡ����������xml�ļ�
	CvHaarClassifierCascade* cascade = (CvHaarClassifierCascade*)cvLoad(cascadeName, 0, 0, 0);
	if( !cascade ) { 
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" ); 
		cvWaitKey(0);
		exit(-1);
    }

	// ֱ��ͼ����
	//cvEqualizeHist(srcImg ,srcImg); 

	// �������
	cvClearMemStorage(storage); 
    objects = cvHaarDetectObjects(	
		srcImg, 
		cascade, 
		storage, 
		scale_factor, 
		min_neighbors, 
		flags, 				/*CV_HAAR_DO_CANNY_PRUNING*/
		min_size
	);
	objectsTemp = objects;	// Ϊ�˽�objects��ֵ���ݻ�main����

	// �ͷ�cascade���ڴ�
	cvReleaseHaarClassifierCascade(&cascade);

}