#pragma once

#ifndef __GETEYEPOS_H__
#define __GETEYEPOS_H__

/******* ���ݻ���ͶӰͼ�����۾����ĵ�ĺ��� *******/
int getEyePos(int* project, int size, int region);

/************************** ����üë�ĺ��� ****************************/
int removeEyebrow(int* horiProject, int width, int height, int threshold);

/********************* �����Զ����ۿ�����ĺ��� *************************/
void calEyeSocketRegion(CvRect* eyeRect, int width, int height, int EyeCol, int EyeRow);

/********************* �����Զ����ۿ�����ĺ��� *************************/
void getEyeMinRect(CvRect* eyeRect, int* horiProject, int* vertProject, int width, int height, int horiThreshold=5, int vertThreshold=3);



#endif