#include <opencv2\opencv.hpp>
#include <vector>
#include <iostream>
#include<stdio.h>
//#include <stdio.h>
//#include <cv.h>  
using namespace std;
using namespace cv;
int main()
{
	CascadeClassifier cascada;
	cascada.load("haarcascade_frontalface_alt2.xml");
	VideoCapture cap(0);
	Mat frame, myFace;
	int pic_num = 1;
	while (1) {
		//����ͷ��ͼ��
		cap >> frame;
		vector<Rect> faces;//vector�������⵽��faces
		Mat frame_gray;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);//ת�ҶȻ�����������
		cascada.detectMultiScale(frame_gray, faces, 1.1, 4, CV_HAAR_DO_ROUGH_SEARCH, Size(70, 70));
		printf("��⵽����������%d\n", faces.size());
		for (int i = 0; i < faces.size(); i++)
		{
			rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
		}
		//��ֻ��һ������ʱ����ʼ���ո�����
		if (faces.size() == 1)
		{
			if (32 == waitKey(20)) {
				Mat faceROI = frame_gray(faces[0]);//�ڻҶ�ͼ�н�Ȧ��������������ü���
			   //cout << faces[0].x << endl;//������face[0].x
				resize(faceROI, myFace, Size(92, 112));//����Ȥ��sizeΪ92*112
				putText(frame, to_string(pic_num), faces[0].tl(), 3, 1.2, (0, 0, 225), 2, 0);//�� faces[0].tl()�����Ͻ�����д���
				string filename = to_string(pic_num) + ".bmp"; //����ڵ�ǰ��Ŀ�ļ�����1-10.jpg/pgm ������format����תΪ�ַ���
				cout << filename << endl;
				imwrite(filename, myFace);//���ڵ�ǰĿ¼��
				imshow(filename, myFace);//��ʾ��size�����
				cout << "����ͼƬ��" << filename << endl;
				waitKey(500);//�ȴ�500us
				destroyWindow(filename);//:����ָ���Ĵ���
				pic_num++;//��ż�1
				if (pic_num == 11)
				{
					return 0;//�����Ϊ11ʱ�˳�ѭ��
				}
			}
				
		}
		int c = waitKey(10);
		if ((char)c == 27) { break; } //10us������esc���˳�ѭ��
		imshow("frame", frame);//��ʾ��Ƶ��
		waitKey(100);//�ȴ�100us
	}
	return 0;
}