#pragma once

#ifndef __DETECTFACE_H__
#define __DETECTFACE_H__
#include<opencv2/imgproc.hpp>

void detectFace(
	IplImage* srcImg,						// �Ҷ�ͼ��
	CvSeq* objects,						// �����������⵽�����ľ��ο�
	CvMemStorage* storage,				// �洢���ο���ڴ�����
	double scale_factor = 1.1,			// �������ڵı���ϵ��
	int min_neighbors = 3,				// ���ɼ��Ŀ������ھ��ε���С����
	int flags = 0,						// ������ʽ
	CvSize min_size = cvSize(20, 20)	// ��ⴰ�ڵ���С�ߴ�
);

#endif