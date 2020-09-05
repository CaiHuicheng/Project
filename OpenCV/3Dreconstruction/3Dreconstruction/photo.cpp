#include <pxcsensemanager.h>  
#include <pxcsession.h>  
#include "util_render.h"  
#include <iostream>  
#include <string>  
#include <stdio.h>  
#include <opencv2\opencv.hpp>
//#include "pxcconvert.h"
 
#define WIDTH 640  
#define HEIGHT 480  
 
using namespace cv;
using namespace std;
 
int main(int argc, char** argv)
{
	UtilRender *renderColor = new UtilRender(L"COLOR_STREAM");
	UtilRender *renderDepth = new UtilRender(L"DEPTH_STREAM");
 
	PXCSenseManager *psm = 0;
	psm = PXCSenseManager::CreateInstance();
	if (!psm)
	{
		wprintf_s(L"Unabel to create the PXCSenseManager\n");
		return 1;
	}
	pxcStatus sts;
 
	psm->EnableStream(PXCCapture::STREAM_TYPE_COLOR, WIDTH, HEIGHT);
 
	psm->EnableStream(PXCCapture::STREAM_TYPE_DEPTH, WIDTH, HEIGHT);
 
	sts = psm->Init();
	if (sts != PXC_STATUS_NO_ERROR)
	{
		wprintf_s(L"Unabel to Initializes the pipeline\n");
		return 2;
	}
 
	PXCImage *colorIm, *depthIm;
	PXCImage::ImageData depth_data, color_data;
	PXCImage::ImageInfo depth_info, color_info;
 
	for (int cframe = 0; cframe < 100; cframe++)
	{
		if (psm->AcquireFrame(true) < PXC_STATUS_NO_ERROR) break;
 
		PXCCapture::Sample *sample = psm->QuerySample();
 
		colorIm = sample->color;
		depthIm = sample->depth;
 
		if (colorIm->AcquireAccess(PXCImage::ACCESS_READ, PXCImage::PIXEL_FORMAT_RGB24, &color_data) < PXC_STATUS_NO_ERROR)
			wprintf_s(L"未正常获取彩色图\n");
		if (depthIm->AcquireAccess(PXCImage::ACCESS_READ, &depth_data) < PXC_STATUS_NO_ERROR)
			wprintf_s(L"未正常获取深度图\n");
 
		depth_info = sample->depth->QueryInfo();
		color_info = sample->color->QueryInfo();
	
		Mat depth(Size(depth_info.width, depth_info.height), CV_16UC1, (void*)depth_data.planes[0], depth_data.pitches[0] /  sizeof(uchar));
		Mat color(Size(color_info.width, color_info.height), CV_8UC3, (void*)color_data.planes[0], color_data.pitches[0] / sizeof(uchar));
		
		if (!renderColor->RenderFrame(colorIm)) break;
		if (!renderDepth->RenderFrame(depthIm)) break;
 
		psm->ReleaseFrame();
 
		stringstream ss;
		string str;
		ss << (cframe);
		str = ss.str();
 
		vector<int> compressiong_params;
		compressiong_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compressiong_params.push_back(0);
 
		imwrite("F:\\programming tools\\VS_workspace\\Projects\\rs_capturepictures\\rs_capturepictures\\color\\color100" + str + ".png", color, compressiong_params);
		imwrite("F:\\programming tools\\VS_workspace\\Projects\\rs_capturepictures\\rs_capturepictures\\depth\\depth100" + str + ".png", depth*15, compressiong_params);
 
	}
	psm->Release();
 
}