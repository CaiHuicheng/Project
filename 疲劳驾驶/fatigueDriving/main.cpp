/*************************************************************************
���ܣ����������������ۣ�ʶ�����۱պ�״̬���ж��Ƿ���ƣ�ͼ�ʻ״̬
�Ľ���
		1. detectFace����������ֱ��ͼ���⻯����ʱ����û�б�Ҫ
		2. ��ֵ����Ч����̫���룬��ʱ��ʵ�ʵļ�ʻͼƬ�����ٿ�����ô�Ľ���
		   ��ֵ��֮ǰһ��Ҫ��ͼ����ǿ�������Ե������ֱ��ͼ���⻯��
		   ��OSTU�ҵ���������ֵ�����ϼ���һ������������̫���ˣ���������ͼƬ�ܻҰ�������¶�ֵ��Ч���ܲ
		3. detectFace�Ӻ�������һ��budge�����ص�objects���Ӻ����ⱻ�ͷ��ˣ�
˵����
**************************************************************************/
#include <stdio.h>
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/face.hpp"
#include "histogram.h"
#include "memory.h"
#include "time.h"
#include "ostuThreshold.h"
#include "detectFace.h"
#include "histProject.h"
#include "linetrans.h"
#include "nonlinetrans.h"
#include "getEyePos.h"
#include "recoEyeState.h"
#include "recoFatigueState.h"

#define DETECTTIME	30								// һ�μ����̵�ʱ�䳤�ȣ��ü���������
#define FATIGUETHRESHOLD	180						// �ж��Ƿ�ƣ�ͼ�ʻ����ֵ
using namespace std;
using namespace cv;
using namespace cv::face;

extern CvSeq* objectsTemp = NULL;					// ����objects��ֵ����main����

int main()
{
/*********************************** �������õ��Ĳ��� ***********************************/ 
	IplImage * srcImg = NULL;						// ��Ŵ�����ͷ��ȡ��ÿһ֡��ɫԴͼ��
	IplImage * img = NULL;							// ��Ŵ�����ͷ��ȡ��ÿһ֡�Ҷ�Դͼ��
	VideoCapture capture;							// VideoCapture ��ȡͼƬ����֡
	CvMemStorage* storage = cvCreateMemStorage(0);	// ��ž��ο����е��ڴ�ռ�
	CvSeq* objects = NULL;							// ��ż�⵽������ƽ�����ο�
	double scale_factor = 1.2;						// �������ڵı���ϵ��
	int min_neighbors = 3;							// ���ɼ��Ŀ������ھ��ε���С����
	int flags = 0;									// ������ʽ
	CvSize min_size = cvSize(40, 40);				// ��ⴰ�ڵ���С�ߴ�
	int i, globalK;								
	int hist[256];									// ���ֱ��ͼ������
	int pixelSum;
	int threshold;									// �洢��ֵ��������ֵ
	clock_t start, stop;							// ��ʱ����
	IplImage* faceImg = NULL;						// �洢����������ͼ��
	int temp = 0;									// ��ʱ�õ��ı���
	int temp1 = 0;									// ��ʱ�õ��ı���
	int count = 0;									// �����õı���
	int flag = 0;									// ��Ǳ���
	int * tempPtr = NULL;							// ��ʱָ��
	CvRect* largestFaceRect;						// �洢��⵽�������������ο�
	int * horiProject = NULL;						// ˮƽ�����ͶӰ���(����ָ��)
	int * vertProject = NULL;						// ��ֱ�����ͶӰ���(����ָ��)
	int * subhoriProject = NULL;					// ˮƽ�����ͶӰ���(����ָ��)
	int * subvertProject = NULL;					// ��ֱ�����ͶӰ���(����ָ��)
	int WIDTH;										// ͼ��Ŀ��
	int HEIGHT;										// ͼ��ĸ߶�
	int rEyeCol = 0;								// �������ڵ�����
	int lEyeCol = 0;								// �������ڵ�����
	int lEyeRow = 0;								// �������ڵ�����
	int rEyeRow = 0;								// �������ڵ�����
	int eyeBrowThreshold;							// ����üë���۾�֮�����ֵ
	uchar* rowPtr = NULL;							// ָ��ͼƬÿ�е�ָ��
	uchar* rowPtrTemp = NULL;						// ָ��ͼƬÿ�е�ָ��, �м����
	IplImage* eyeImg = NULL;						// �洢�۾���ͼ��
	CvRect eyeRect;									// �洢�ü�������۵ľ�������
	CvRect eyeRectTemp;								// ��ʱ��������
	IplImage* lEyeImg = NULL;						// �洢���۵�ͼ��
	IplImage* rEyeImg = NULL;						// �洢���۵�ͼ��
	IplImage* lEyeImgNoEyebrow = NULL;				// �洢ȥ��üë֮�������ͼ��
	IplImage* rEyeImgNoEyebrow = NULL;				// �洢ȥ��üë֮�������ͼ��
	IplImage* lEyeballImg = NULL;					// �洢���շָ�����ۿ��ͼ��
	IplImage* rEyeballImg = NULL;					// �洢���շָ�����ۿ��ͼ��
	IplImage* lMinEyeballImg = NULL;				// �洢���շָ����С�����ۿ��ͼ��
	IplImage* rMinEyeballImg = NULL;				// �洢���շָ����С�����ۿ��ͼ��
	int lMinEyeballBlackPixel;						// �洢���շָ����С�����ۿ�İ�ɫ���ظ���
	int rMinEyeballBlackPixel;						// �洢���շָ����С�����ۿ�İ�ɫ���ظ���
	double lMinEyeballBlackPixelRate;				// �洢���շָ����С�����ۿ�ĺ�ɫ����ռ�ı���
	double rMinEyeballBlackPixelRate;				// �洢���շָ����С�����ۿ�ĺ�ɫ����ռ�ı���
	double lMinEyeballRectShape;					// �洢��С���ۿ��ľ��γ����ֵ
	double rMinEyeballRectShape;					// �洢��С���ۿ��ľ��γ����ֵ
	double lMinEyeballBeta;							// �洢��С���ۿ����м�1/2����ĺ����ر�ֵ
	double rMinEyeballBeta;							// �洢��С�ұ��ۿ����м�1/2����ĺ����ر�ֵ
	int lEyeState;									// ��������0�����գ�1��״̬
	int rEyeState;									// ��������0�����գ�1��״̬
	int eyeState;									// �۾��ۺ�����0�����գ�1��״̬
	int eyeCloseNum = 0;							// ͳ��һ�μ������б��۵�����
	int eyeCloseDuration = 0;						// ͳ��һ�μ�������������⵽����״̬�Ĵ���
	int maxEyeCloseDuration = 0;					// һ�μ�������������⵽����״̬�Ĵ��������ֵ
	int failFaceNum = 0;							// ͳ��һ�μ�������δ��⵽����������
	int failFaceDuration = 0;						// ͳ��һ�μ�����������δ��⵽�����Ĵ���
	int maxFailFaceDuration = 0;					// һ�μ�����������δ��⵽�����Ĵ��������ֵ
	int fatigueState = 1;							// ��ʻԱ�ļ�ʻ״̬��ƣ�ͼ�ʻ��1����������ʻ��0��

	/********************* ������ʾ���� **************************/
	cvNamedWindow("img", CV_WINDOW_AUTOSIZE);		// ��ʾ�Ҷ�Դͼ��
	cvNamedWindow("�ָ�������", 1);				// ��ʾ�ָ�������ۿ����������
	cvNamedWindow("���µ���������", 1);				// ��ʾ���µ���������
	cvNamedWindow("���µ���������", 1);				// ��ʾ���µ���������
	cvNamedWindow("l_binary");						// ��ʾ������������Ķ�ֵ��ͼ��
	cvNamedWindow("r_binary");						// ��ʾ������������Ķ�ֵ��ͼ��
	cvNamedWindow("lEyeImgNoEyebrow", 1);			// ��ʾȥ��üë���������ͼ��
	cvNamedWindow("rEyeImgNoEyebrow", 1);			// ��ʾȥ��üë���������ͼ��
	cvNamedWindow("lEyeCenter", 1);					// ��ʾ�����Ĥ���ĵ�����ͼ��
	cvNamedWindow("rEyeCenter", 1);					// ��ʾ�����Ĥ���ĵ�����ͼ��
	cvNamedWindow("lEyeballImg", 1);				// ����lEyeImgNoEyebrow��С��1/2�������»��ֵ�����ͼ��
	cvNamedWindow("rEyeballImg", 1);				// ����rEyeImgNoEyebrow��С��1/2�������»��ֵ�����ͼ��
	cvNamedWindow("lkai", 1);						// ���۽��п�����֮���ͼ��
	cvNamedWindow("rkai", 1);						// ���۽��п�����֮���ͼ��
	cvNamedWindow("lMinEyeballImg", 1);				// ��С���߽���������ۺ�Ĥͼ��
	cvNamedWindow("rMinEyeballImg", 1);				// ��С���߽�����������ۺ�Ĥͼ��
	
	Mat frame;
	capture.open(0);
	if (!capture.isOpened()) { 
		printf("--(!)Error opening video capture\n"); 
		return -1;
	}

	for( globalK = 1; globalK <= DETECTTIME; globalK ++ ){
		start = clock();
		capture.read(frame);
		srcImg = cvCloneImage(&(IplImage)frame);
		img = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U, 1);
		cvCvtColor(srcImg, img, CV_BGR2GRAY);
		if( !img )
			continue;
		cvShowImage("img", img);
		cvWaitKey(20);

	/************************************* ������� ****************************************/
		cvClearMemStorage(storage);	// ���洢��� top �õ��洢���ͷ��������մ洢���еĴ洢����
		detectFace(
			img,					// �Ҷ�ͼ��
			objects,				// �����������⵽�����ľ��ο�
			storage,				// �洢���ο���ڴ�����
			scale_factor,			// �������ڵı���ϵ��
			min_neighbors,			// ���ɼ��Ŀ������ھ��ε���С����
			flags,					// ������ʽ
			cvSize(20, 20)			// ��ⴰ�ڵ���С�ߴ�
		);

		// ��ȡ��������
		if ( !objectsTemp->total ){
			printf("Failed to detect face!\n");		// ���Դ���
			failFaceNum ++;							// ͳ��δ��⵽�����Ĵ���
			failFaceDuration ++;					// ͳ������δ��⵽�����Ĵ���

			// ���������ж�ȫ�Ǳ��ۺͼ�ⲻ�������������û�������۵����������maxEyeCloseDuration = 0;
			(eyeCloseDuration > maxEyeCloseDuration) ? maxEyeCloseDuration = eyeCloseDuration : maxEyeCloseDuration;
			eyeCloseDuration = 0;

			if( globalK == DETECTTIME ){
				// ��һ�μ������У����еĹ��̶���ⲻ����������Ҫ�ڴ˸��� maxFailFaceDuration 
				(failFaceDuration > maxFailFaceDuration) ? maxFailFaceDuration = failFaceDuration : maxFailFaceDuration;

				printf("\nFATIGUETHRESHOLD: %d\n", FATIGUETHRESHOLD);
				printf("eyeCloseNum: %d\tmaxEyeCloseDuration: %d\n", eyeCloseNum, maxEyeCloseDuration);
				printf("failFaceNum: %d\tmaxFailFaceDuration: %d\n", failFaceNum, maxFailFaceDuration);
				
				// ����ƣ��״̬���б�
				fatigueState = recoFatigueState(FATIGUETHRESHOLD, eyeCloseNum, maxEyeCloseDuration, failFaceNum, maxFailFaceDuration);
				if( fatigueState == 1 )
					printf("��ʻԱ����ƣ�ͼ�ʻ״̬\n\n");
				else if( fatigueState == 0 )
					printf("��ʻԱ����������ʻ״̬\n\n");

				// ������һ�μ�����ǰ������������
				globalK = 0;
				lEyeState = 1;
				rEyeState = 1;
				eyeState = 1;
				eyeCloseNum = 0;
				eyeCloseDuration = 0;
				maxEyeCloseDuration = 0;
				failFaceNum = 0;
				failFaceDuration = 0;
				maxFailFaceDuration = 0;
				fatigueState = 1;

				cvWaitKey(0);
			}

			continue;
		}
		else{
			// ͳ������δ��⵽�����Ĵ����е������ֵ
			(failFaceDuration > maxFailFaceDuration) ? maxFailFaceDuration = failFaceDuration : maxFailFaceDuration;
			failFaceDuration = 0;
			// �ҵ���⵽������������������
			temp = 0;
			for(i = 0; i < (objectsTemp ? objectsTemp->total : 0); i ++) {
				CvRect* rect = (CvRect*) cvGetSeqElem(objectsTemp, i);
				if ( (rect->height * rect->width) > temp ){
					largestFaceRect = rect;
					temp = rect->height * rect->width;
				}
			}

			// ��������������֪ʶ�ָ�����µ���������
			temp = largestFaceRect->width / 8;
			largestFaceRect->x = largestFaceRect->x + temp;
			largestFaceRect->width = largestFaceRect->width - 3*temp/2;
			largestFaceRect->height = largestFaceRect->height / 2;
			largestFaceRect->y = largestFaceRect->y + largestFaceRect->height / 2;
			largestFaceRect->height = largestFaceRect->height / 2;

			cvSetImageROI(img, *largestFaceRect);		// ����ROIΪ��⵽��������������
			faceImg = cvCreateImage(cvSize(largestFaceRect->width, largestFaceRect->height), IPL_DEPTH_8U, 1);
			cvCopy(img, faceImg, NULL);
			cvResetImageROI(img);						// �ͷ�ROI
			cvShowImage("�ָ�������", faceImg);

			eyeRectTemp = *largestFaceRect;
			// ��������������֪ʶ�ָ�����µ���������
			largestFaceRect->width /= 2;
			cvSetImageROI(img, *largestFaceRect);		// ����ROIΪ��⵽��������������
			lEyeImg = cvCreateImage(cvSize(largestFaceRect->width, largestFaceRect->height), IPL_DEPTH_8U, 1);
			cvCopy(img, lEyeImg, NULL);
			cvResetImageROI(img);						// �ͷ�ROI
			cvShowImage("���µ���������", lEyeImg);

			// ��������������֪ʶ�ָ�����µ���������
 			eyeRectTemp.x += eyeRectTemp.width / 2;
			eyeRectTemp.width /= 2;
			cvSetImageROI(img, eyeRectTemp);		// ����ROIΪ��⵽��������������
			rEyeImg = cvCreateImage(cvSize(eyeRectTemp.width, eyeRectTemp.height), IPL_DEPTH_8U, 1);
			cvCopy(img, rEyeImg, NULL);
			cvResetImageROI(img);						// �ͷ�ROI
			cvShowImage("���µ���������", rEyeImg);

		/********************************** ��ֵ������ ***********************************/
			// ͼ����ǿ��ֱ��ͼ���⻯��detectFace��ʵ����һ�Σ��ɳ��Է����Ե�����
			/*** ��ֵ�����۴��������ͼ�� ***/
			//lineTrans(lEyeImg, lEyeImg, 1.5, 0);		// ���Ե�����
			cvSmooth(lEyeImg, lEyeImg, CV_MEDIAN);		// ��ֵ�˲� Ĭ�ϴ��ڴ�СΪ3*3
			nonlineTrans(lEyeImg, lEyeImg, 0.8);		// �����Ե�����
			memset(hist, 0, sizeof(hist));				// ��ʼ��ֱ��ͼ������Ϊ0
			histogram(lEyeImg, hist);					// ����ͼƬֱ��ͼ
			// ���������ֵ
			pixelSum = lEyeImg->width * lEyeImg->height;
			threshold = ostuThreshold(hist, pixelSum, 45);
			cvThreshold(lEyeImg, lEyeImg, threshold, 255, CV_THRESH_BINARY);// ��ͼ���ֵ��
			// ��ʾ��ֵ�����ͼ��
			cvShowImage("l_binary",lEyeImg);

			/*** ��ֵ�����۴��������ͼ�� ***/
			//lineTrans(rEyeImg, rEyeImg, 1.5, 0);		// ���Ե�����
			cvSmooth(rEyeImg, rEyeImg, CV_MEDIAN);		// ��ֵ�˲� Ĭ�ϴ��ڴ�СΪ3*3
			nonlineTrans(rEyeImg, rEyeImg, 0.8);		// �����Ե�����
			memset(hist, 0, sizeof(hist));				// ��ʼ��ֱ��ͼ������Ϊ0
			histogram(rEyeImg, hist);					// ����ͼƬֱ��ͼ
			// ���������ֵ
			pixelSum = rEyeImg->width * rEyeImg->height;
			threshold = ostuThreshold(hist, pixelSum, 45);
			cvThreshold(rEyeImg, rEyeImg, threshold, 255, CV_THRESH_BINARY);// ��ͼ���ֵ��
			// ��ʾ��ֵ�����ͼ��
			cvShowImage("r_binary",rEyeImg);

		/***************************************** ������� ********************************************/
			/** ��������Ե�üë������ָ�ȥ��üë **/

			// �ָ�����üë
			HEIGHT = lEyeImg->height;
			WIDTH = lEyeImg->width;
			// �����ڴ�
			horiProject = (int*)malloc(HEIGHT * sizeof(int));
			vertProject = (int*)malloc(WIDTH * sizeof(int));
			if( horiProject == NULL || vertProject == NULL ){
				printf("Failed to allocate memory\n");
				cvWaitKey(0);
				return -1;
			}
			// �ڴ�����
			for(i = 0; i < HEIGHT; i ++)
				*(horiProject + i) = 0;
			for(i = 0; i < WIDTH; i ++)
				*(vertProject + i) = 0;
			histProject(lEyeImg, horiProject, vertProject);				// ����ֱ��ͼͶӰ
			lEyeRow = removeEyebrow(horiProject, WIDTH, HEIGHT, 10);	// ����ָ�üë���ۿ��λ��

			// �ָ�����üë
			HEIGHT = rEyeImg->height;
			WIDTH = rEyeImg->width;
			// �����ڴ�
			horiProject = (int*)malloc(HEIGHT * sizeof(int));
			vertProject = (int*)malloc(WIDTH * sizeof(int));
			if( horiProject == NULL || vertProject == NULL ){
				printf("Failed to allocate memory\n");
				cvWaitKey(0);
				return -1;
			}
			// �ڴ�����
			for(i = 0; i < HEIGHT; i ++)
				*(horiProject + i) = 0;
			for(i = 0; i < WIDTH; i ++)
				*(vertProject + i) = 0;
			histProject(rEyeImg, horiProject, vertProject);				// ����ֱ��ͼͶӰ
			rEyeRow = removeEyebrow(horiProject, WIDTH, HEIGHT, 10);	// ����ָ�üë���ۿ��λ��

			// ��ʾȥ��üë������۴�������
			eyeRect = cvRect(0, lEyeRow, lEyeImg->width, (lEyeImg->height - lEyeRow));		// ȥüë���ۿ�������lEyeImg�еľ��ο�����
			cvSetImageROI(lEyeImg, eyeRect);							// ����ROIΪȥ��üë���ۿ����������ͷ�ROI
			lEyeImgNoEyebrow = cvCreateImage(cvSize(eyeRect.width, eyeRect.height), IPL_DEPTH_8U, 1);
			cvCopy(lEyeImg, lEyeImgNoEyebrow, NULL);
			cvShowImage("lEyeImgNoEyebrow", lEyeImgNoEyebrow);

			eyeRectTemp = cvRect(0, rEyeRow, rEyeImg->width, (rEyeImg->height - rEyeRow));	// ȥüë���ۿ�������rEyeImg�еľ��ο�����
			cvSetImageROI(rEyeImg, eyeRectTemp);						// ����ROIΪȥ��üë���ۿ����������ͷ�ROI
			rEyeImgNoEyebrow = cvCreateImage(cvSize(eyeRectTemp.width, eyeRectTemp.height), IPL_DEPTH_8U, 1);
			cvCopy(rEyeImg, rEyeImgNoEyebrow, NULL);
			cvShowImage("rEyeImgNoEyebrow", rEyeImgNoEyebrow);

			///////////////// ��λ�۾����ĵ���ȥ��üëͼ���е�����λ�� ///////////////////
			HEIGHT = lEyeImgNoEyebrow->height;
			WIDTH = lEyeImgNoEyebrow->width;
			// �����ڴ�
			subhoriProject = (int*)malloc(HEIGHT * sizeof(int));
			subvertProject = (int*)malloc(WIDTH * sizeof(int));
			if( subhoriProject == NULL || subvertProject == NULL ){
				printf("Failed to allocate memory\n");
				cvWaitKey(0);
				return -1;
			}
			// �ڴ�����
			for(i = 0; i < HEIGHT; i ++)
				*(subhoriProject + i) = 0;
			for(i = 0; i < WIDTH; i ++)
				*(subvertProject + i) = 0;
	
			histProject(lEyeImgNoEyebrow, subhoriProject, subvertProject);	// ���¶Էָ��������ͼ����л���ͶӰ
			lEyeRow = getEyePos(subhoriProject, HEIGHT, HEIGHT/5);	// ��λ�������ڵ���
			lEyeCol = getEyePos(subvertProject, WIDTH, WIDTH/5);	// ��λ�������ڵ���


			HEIGHT = rEyeImgNoEyebrow->height;
			WIDTH = rEyeImgNoEyebrow->width;
			// �����ڴ�
			subhoriProject = (int*)malloc(HEIGHT * sizeof(int));
			subvertProject = (int*)malloc(WIDTH * sizeof(int));
			if( subhoriProject == NULL || subvertProject == NULL ){
				printf("Failed to allocate memory\n");
				cvWaitKey(0);
				return -1;
			}
			// �ڴ�����
			for(i = 0; i < HEIGHT; i ++)
				*(subhoriProject + i) = 0;
			for(i = 0; i < WIDTH; i ++)
				*(subvertProject + i) = 0;
			histProject(rEyeImgNoEyebrow, subhoriProject, subvertProject);	// ���¶Էָ��������ͼ����л���ͶӰ
			rEyeRow = getEyePos(subhoriProject, HEIGHT, HEIGHT/5);	// ��λ�������ڵ���
			rEyeCol = getEyePos(subvertProject, WIDTH,  WIDTH/5);	// ��λ�������ڵ���
			/*
			printf("************ image of eyes without eyebrow ***********\n");
			printf("Left eye: width: %d\theight: %d\n", lEyeImgNoEyebrow->width, lEyeImgNoEyebrow->height);
			printf("Right eye: width: %d\theight: %d\n", rEyeImgNoEyebrow->width, rEyeImgNoEyebrow->height);
			printf("Right eye: WIDTH: %d\tHEIGHT: %d\n", WIDTH, HEIGHT);
			printf("Centers positon of Eyes. lEyeRow: %d lEyeCol: %d\trEyeRow: %d rEyeCol: %d\n\n", lEyeRow, lEyeCol, rEyeRow, rEyeCol);
			*/
			// ����۾���λ��
			cvCircle(lEyeImgNoEyebrow, cvPoint(lEyeCol, lEyeRow), 3, CV_RGB(0,0,255), 1, 8, 0);
			cvCircle(rEyeImgNoEyebrow, cvPoint(rEyeCol, rEyeRow), 3, CV_RGB(0,0,255), 1, 8, 0);
			cvShowImage("lEyeCenter", lEyeImgNoEyebrow);
			cvShowImage("rEyeCenter", rEyeImgNoEyebrow);
	

		/********************************** �ж���������״̬ ***********************************/
	
			////////////////// �ָ�����ҵ�������Ϊ���ĵĴ����ۿ� /////////////////
			// ���ۿ�
			HEIGHT = lEyeImgNoEyebrow->height;
			WIDTH = lEyeImgNoEyebrow->width;
			// ��������ۿ�������: eyeRect
			eyeRect = cvRect(0, 0, WIDTH, HEIGHT);
			calEyeSocketRegion(&eyeRect, WIDTH, HEIGHT, lEyeCol, lEyeRow);
			/*
			printf("************lEyeImgNoEyebrow************\n");
			printf("width: %d\theight: %d\n", WIDTH, HEIGHT);
			printf("**********lEyeballRect**********\n");
			printf("eyeRect.x = %d\teyeRect.width = %d\n", eyeRect.x, eyeRectTemp.width);
			printf("eyeRect.y = %d\teyeRect.height = %d\n\n", eyeRectTemp.y, eyeRectTemp.height);
			*/
			cvSetImageROI(lEyeImgNoEyebrow, eyeRect);		// ����ROIΪ��⵽�ۿ�����
			lEyeballImg = cvCreateImage(cvGetSize(lEyeImgNoEyebrow), IPL_DEPTH_8U, 1);
			cvCopy(lEyeImgNoEyebrow, lEyeballImg, NULL);
			cvResetImageROI(lEyeImgNoEyebrow);
			cvShowImage("lEyeballImg", lEyeballImg);

			// ���ۿ�
			HEIGHT = rEyeImgNoEyebrow->height;
			WIDTH = rEyeImgNoEyebrow->width;
			// ��������ۿ�������: eyeRectTemp
			eyeRect = cvRect(0, 0, WIDTH, HEIGHT);
			calEyeSocketRegion(&eyeRect, WIDTH, HEIGHT, rEyeCol, rEyeRow);
			/*
			printf("************rEyeImgNoEyebrow************\n");
			printf("width: %d\theight: %d\n", WIDTH, HEIGHT);
			printf("**********rEyeballRect**********\n");
			printf("eyeRect.x = %d\teyeRect.width = %d\n", eyeRect.x, eyeRect.width);
			printf("eyeRect.y = %d\teyeRect.height = %d\n\n", eyeRect.y, eyeRect.height);
			*/
			cvSetImageROI(rEyeImgNoEyebrow, eyeRect);		// ����ROIΪ��⵽�ۿ�����
			rEyeballImg = cvCreateImage(cvGetSize(rEyeImgNoEyebrow), IPL_DEPTH_8U, 1);
			cvCopy(rEyeImgNoEyebrow, rEyeballImg, NULL);
			cvResetImageROI(rEyeImgNoEyebrow);
			cvShowImage("rEyeballImg", rEyeballImg);

			/////////////////////////// ������ ///////////////////////////
			cvErode(lEyeballImg, lEyeballImg, NULL, 2);		//��ʴͼ��  
			cvDilate(lEyeballImg, lEyeballImg, NULL, 2);	//����ͼ��
			cvShowImage("lkai", lEyeballImg);

			cvErode(rEyeballImg, rEyeballImg, NULL, 1);		//��ʴͼ��  
			cvDilate(rEyeballImg, rEyeballImg, NULL, 1);	//����ͼ��
			cvShowImage("rkai", rEyeballImg);

			/////////////////// ������С�۾��ľ������� ////////////////////
	
			///////////////////////////����
			HEIGHT = lEyeballImg->height;
			WIDTH = lEyeballImg->width;

			// �����ڴ�
			subhoriProject = (int*)malloc(HEIGHT * sizeof(int));
			subvertProject = (int*)malloc(WIDTH * sizeof(int));
			if( subhoriProject == NULL || subvertProject == NULL ){
				printf("Failed to allocate memory\n");
				cvWaitKey(0);
				return -1;
			}
			// �ڴ�����
			for(i = 0; i < HEIGHT; i ++)
				*(subhoriProject + i) = 0;
			for(i = 0; i < WIDTH; i ++)
				*(subvertProject + i) = 0;
			histProject(lEyeballImg, subhoriProject, subvertProject);
			// ����������С�ľ�������
			eyeRectTemp = cvRect(0, 0 , 1, 1);		// ��ʼ��
			getEyeMinRect(&eyeRectTemp, subhoriProject, subvertProject, WIDTH, HEIGHT, 5, 3);
			/*
			printf("eyeRectTemp.y: %d\n", eyeRectTemp.y);
			printf("eyeRectTemp.height: %d\n", eyeRectTemp.height);
			printf("eyeRectTemp.x: %d\n", eyeRectTemp.x);
			printf("eyeRectTemp.width: %d\n", eyeRectTemp.width);
			*/
			// ������С���۾��εĳ����,  �ж��۾�״̬ʱ�õĵ�
			lMinEyeballRectShape = (double)eyeRectTemp.width / (double)eyeRectTemp.height;
			//printf("\nlMinEyeballRectShape: %f\n", lMinEyeballRectShape);

			cvSetImageROI(lEyeballImg, eyeRectTemp);		// ����ROIΪ��⵽��С������ۿ�
			lMinEyeballImg = cvCreateImage(cvGetSize(lEyeballImg), IPL_DEPTH_8U, 1);
			cvCopy(lEyeballImg, lMinEyeballImg, NULL);
			cvResetImageROI(lEyeballImg);
			cvShowImage("lMinEyeballImg", lMinEyeballImg);

			////////////////////////  ͳ�����ۺ����ظ���  /////////////////////
			HEIGHT = lMinEyeballImg->height;
			WIDTH = lMinEyeballImg->width;

			// �����ڴ�
			subhoriProject = (int*)malloc(HEIGHT * sizeof(int));
			subvertProject = (int*)malloc(WIDTH * sizeof(int));
			if( subhoriProject == NULL || subvertProject == NULL ){
				printf("Failed to allocate memory\n");
				cvWaitKey(0);
				return -1;
			}
			// �ڴ�����
			for(i = 0; i < HEIGHT; i ++)
				*(subhoriProject + i) = 0;
			for(i = 0; i < WIDTH; i ++)
				*(subvertProject + i) = 0;

			histProject(lMinEyeballImg, subhoriProject, subvertProject);

			// ͳ��lEyeballImg�к�ɫ���صĸ���
			temp = 0;	// �����ظ���
			for( i = 0; i < WIDTH; i ++ )
				temp += *(subvertProject + i);
			temp /= 255;
			lMinEyeballBlackPixel = WIDTH * HEIGHT - temp;
			lMinEyeballBlackPixelRate = (double)lMinEyeballBlackPixel / (double)(WIDTH * HEIGHT);
			//printf("WIDTH * HEIGHT: %d\tlMinEyeballBlackSum;%d\n\n", WIDTH * HEIGHT, lMinEyeballBlackPixel);
			//printf("lMinEyeballBlackPixelRate;%f\n\n", lMinEyeballBlackPixelRate);

			// ͳ��lMinEyeballImg�е�1/2�����ں����صı���
			lMinEyeballBeta = 0;
			lMinEyeballBeta = calMiddleAreaBlackPixRate(subvertProject, &eyeRectTemp, WIDTH, HEIGHT, lEyeCol, lMinEyeballBlackPixel);

			//printf("lMinEyeballBeta; %f\n\n", lMinEyeballBeta);



			////////////////////////////////////����
			HEIGHT = rEyeballImg->height;
			WIDTH = rEyeballImg->width;
			// �����ڴ�
			subhoriProject = (int*)malloc(HEIGHT * sizeof(int));
			subvertProject = (int*)malloc(WIDTH * sizeof(int));
			if( subhoriProject == NULL || subvertProject == NULL ){
				printf("Failed to allocate memory\n");
				cvWaitKey(0);
				return -1;
			}
			// �ڴ�����
			for(i = 0; i < HEIGHT; i ++)
				*(subhoriProject + i) = 0;
			for(i = 0; i < WIDTH; i ++)
				*(subvertProject + i) = 0;
			histProject(rEyeballImg, subhoriProject, subvertProject);

			// ����������С�ľ�������
			eyeRectTemp = cvRect(0, 0 , 1, 1);
			getEyeMinRect(&eyeRectTemp, subhoriProject, subvertProject, WIDTH, HEIGHT, 5, 3);

			// ������С���۾��εĳ���ȣ��ж��۾�״̬ʱ�õĵ�
			rMinEyeballRectShape = (double)eyeRectTemp.width / (double)eyeRectTemp.height;
			//printf("\nrMinEyeballRectShape: %f\n", rMinEyeballRectShape);

			cvSetImageROI(rEyeballImg, eyeRectTemp);		// ����ROIΪ��⵽��С������ۿ�
			rMinEyeballImg = cvCreateImage(cvGetSize(rEyeballImg), IPL_DEPTH_8U, 1);
			cvCopy(rEyeballImg, rMinEyeballImg, NULL);
			cvResetImageROI(rEyeballImg);
			cvShowImage("rMinEyeballImg", rMinEyeballImg);

			////////////////////////  ͳ�����ۺ����ظ���  /////////////////////
			HEIGHT = rMinEyeballImg->height;
			WIDTH = rMinEyeballImg->width;

			// �����ڴ�
			subhoriProject = (int*)malloc(HEIGHT * sizeof(int));
			subvertProject = (int*)malloc(WIDTH * sizeof(int));
			if( subhoriProject == NULL || subvertProject == NULL ){
				printf("Failed to allocate memory\n");
				cvWaitKey(0);
				return -1;
			}
			// �ڴ�����
			for(i = 0; i < HEIGHT; i ++)
				*(subhoriProject + i) = 0;
			for(i = 0; i < WIDTH; i ++)
				*(subvertProject + i) = 0;
			histProject(rMinEyeballImg, subhoriProject, subvertProject);// ����ֱ��ͼ����ͶӰ

			// ͳ��lEyeballImg�к�ɫ���صĸ���
			temp = 0;
			for( i = 0; i < WIDTH; i ++ )
				temp += *(subvertProject + i);
			temp /= 255;
			rMinEyeballBlackPixel = WIDTH * HEIGHT - temp;
			rMinEyeballBlackPixelRate = (double)rMinEyeballBlackPixel / (double)(WIDTH * HEIGHT);
			//printf("WIDTH * HEIGHT: %d\trMinEyeballBlackSum;%d\n\n", WIDTH * HEIGHT, rMinEyeballBlackPixel);
			//printf("rMinEyeballBlackPixelRate; %f\n\n", rMinEyeballBlackPixelRate);

			// ͳ��lMinEyeballImg�е�1/2�����ں����صı���
			rMinEyeballBeta = 0;
			rMinEyeballBeta = calMiddleAreaBlackPixRate(subvertProject, &eyeRectTemp, WIDTH, HEIGHT, rEyeCol, rMinEyeballBlackPixel);

			//printf("temp:%d\trMinEyeballBeta; %f\n\n", temp, rMinEyeballBeta);

			// �ж��۾��������
			lEyeState = 1;		// ����״̬��Ĭ�ϱ���
			rEyeState = 1;		// ����״̬��Ĭ�ϱ���
			eyeState = 1;		// �۾��ۺ�״̬��Ĭ�ϱ���
			if( lMinEyeballBlackPixel > 50)
				lEyeState = getEyeState(lMinEyeballRectShape, lMinEyeballBlackPixelRate, lMinEyeballBeta);
			else
				lEyeState = 1;

			if( rMinEyeballBlackPixel > 50)
				rEyeState = getEyeState(rMinEyeballRectShape, rMinEyeballBlackPixelRate, rMinEyeballBeta);
			else
				rEyeState = 1;
			(lEyeState + rEyeState) == 2 ? eyeState = 1 : eyeState=0;

			// ͳ���۾��պϵĴ���
			if( eyeState == 1 ){
				eyeCloseNum ++;					// ͳ�� eyeCloseNum �۾��պϴ���
				eyeCloseDuration ++;
				if( globalK == DETECTTIME){
					// ���������ж�ȫ�Ǳ��������û�����ۺͼ�ⲻ�����������
					(eyeCloseDuration > maxEyeCloseDuration) ? maxEyeCloseDuration = eyeCloseDuration : maxEyeCloseDuration;
					eyeCloseDuration = 0;
				}
			}
			else{
				(eyeCloseDuration > maxEyeCloseDuration) ? maxEyeCloseDuration = eyeCloseDuration : maxEyeCloseDuration;
				eyeCloseDuration = 0;
			}
		} // �н��ж��Ƿ��⵽������if���

	/*	
		printf("\n************** �۾�״̬ ***************\n");
		printf("lEyeState: %d\trEyeState: %d\n", lEyeState, rEyeState);
		printf("eyeState: %d\n\n\n\n", eyeState);
	*/

		// ��ʱ��ִ��һ��ѭ����ʱ��
		stop = clock();
		//printf("run time: %f\n", (double)(stop - start) / CLOCKS_PER_SEC);

		printf("eyeState: %d\n", eyeState);

		// ����ѭ��������������һ�μ�����
		if( globalK == DETECTTIME ){
			printf("\nFATIGUETHRESHOLD*****: %d\n", FATIGUETHRESHOLD);
			printf("eyeCloseNum: %d\tmaxEyeCloseDuration: %d\n", eyeCloseNum, maxEyeCloseDuration);
			printf("failFaceNum: %d\tmaxFailFaceDuration: %d\n", failFaceNum, maxFailFaceDuration);

			// ����ƣ��״̬���б�
			fatigueState = recoFatigueState(FATIGUETHRESHOLD, eyeCloseNum, maxEyeCloseDuration, failFaceNum, maxFailFaceDuration);
			if( fatigueState == 1 )
				printf("��ʻԱ����ƣ�ͼ�ʻ״̬\n\n");
			else if( fatigueState == 0 )
				printf("��ʻԱ����������ʻ״̬\n\n");

			// ������һ�μ�����ǰ������������
			globalK = 0;
			lEyeState = 1;
			rEyeState = 1;
			eyeState = 1;
			eyeCloseNum = 0;
			eyeCloseDuration = 0;
			maxEyeCloseDuration = 0;
			failFaceNum = 0;
			failFaceDuration = 0;
			maxFailFaceDuration = 0;
			fatigueState = 1;
			char c = cvWaitKey(0);
			if( c == 27 )
				break;
			else
				continue;
		}
	} // �нӼ����̵� for ѭ��

	// �ͷ��ڴ�
	cvDestroyWindow("�ָ�������");
	cvDestroyWindow("���µ���������");
	cvDestroyWindow("���µ���������");
	cvDestroyWindow("l_binary");
	cvDestroyWindow("r_binary");
	cvDestroyWindow("lEyeImgNoEyebrow");
	cvDestroyWindow("rEyeImgNoEyebrow");
	cvDestroyWindow("lEyeCenter");
	cvDestroyWindow("rEyeCenter");	
	cvDestroyWindow("lEyeballImg");
	cvDestroyWindow("rEyeballImg");
	cvDestroyWindow("lkai");
	cvDestroyWindow("rkai");
	cvDestroyWindow("lMinEyeballImg");
	cvDestroyWindow("rMinEyeballImg");
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&eyeImg);
	free(horiProject);
	free(vertProject);
	free(subhoriProject);
	free(subvertProject);

	return 0;
}