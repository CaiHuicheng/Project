#pragma once

#ifndef __RECOEYESTATE_H__
#define __RECOEYESTATE_H__

// ����ģ���ۺ�����˼�������۾��������պ�״̬
int getEyeState(double MinEyeballRectShape, double MinEyeballBlackPixelRate, double MinEyeballBeta);

// ����ģ��ģʽʶ�������۾��������պ�״̬
int FuzPatternRecoEyeState(double MinEyeballRectShape, double MinEyeballBlackPixelRate, double MinEyeballBeta);

// ͳ��lMinEyeballImg�е�1/2�����ں����صı���
double calMiddleAreaBlackPixRate(int* vertProject, CvRect* eyeRect, int width, int height, int eyeCol, int MinEyeballBlackPixel);


#endif