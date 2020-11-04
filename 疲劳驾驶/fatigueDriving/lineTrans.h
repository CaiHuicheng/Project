#pragma once

#ifndef __LINETRANS_H__
#define __LINETRANS_H__
#include<opencv2/imgproc.hpp>

void lineTrans(IplImage* srcImg, IplImage* dstImg, float a, float b);

#endif