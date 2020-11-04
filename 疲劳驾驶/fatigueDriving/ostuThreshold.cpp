/******************************************************
���ܣ���Ostu�����䷽������ֵ����ֵ
���룺
	hist��ͼ���ֱ��ͼ����
	pixelSum��ͼ��������ܺ�
	CONST: һ��������Ϊ����Ӧ���������Ҫ�󣬿�ʵ�����ҵ������ŷָ���ֵ�Ļ����ϼ�ȥ�ó���
�����
	threshold��������ֵ
******************************************************/
#pragma once

#include <stdio.h>

int ostuThreshold(int * hist, int pixelSum, const int CONST)
{
	float pixelPro[256];
	int i, j, threshold = 0;

	//����ÿ������������ͼ���еı���
	for(i = 0; i < 256; i++){
		*(pixelPro+i) = (float)(*(hist+i)) / (float)(pixelSum);
	}

	//����ostu�㷨,�õ�ǰ���ͱ����ķָ�
	//�����Ҷȼ�[0,255],������������ĻҶ�ֵ,Ϊ�����ֵ
	float w0, w1, u0tmp, u1tmp, u0, u1, u,deltaTmp, deltaMax = 0;
	for(i = 0; i < 256; i++){
		w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;

		for(j = 0; j < 256; j++){
			if(j <= i){			//��������
				//��iΪ��ֵ���࣬��һ���ܵĸ���
				w0 += *(pixelPro+j);		
				u0tmp += j * (*(pixelPro+j));
			}
			else				//ǰ������
			{
				//��iΪ��ֵ���࣬�ڶ����ܵĸ���
				w1 += *(pixelPro+j);		
				u1tmp += j * (*(pixelPro+j));
			}
		}

		u0 = u0tmp / w0;		//��һ���ƽ���Ҷ�
		u1 = u1tmp / w1;		//�ڶ����ƽ���Ҷ�
		u = u0tmp + u1tmp;		//����ͼ���ƽ���Ҷ�
		//������䷽��
		deltaTmp = w0 * (u0 - u)*(u0 - u) + w1 * (u1 - u)*(u1 - u);
		//�ҳ������䷽���Լ���Ӧ����ֵ
		if(deltaTmp > deltaMax){	
			deltaMax = deltaTmp;
			threshold = i;
		}
	}
	//printf("Ostu Threshold: %d\n", threshold);
	//printf("real Threshold: %d\n", threshold - CONST);
	//���������ֵ;
	return (threshold - CONST);
}