#include <opencv2\imgcodecs.hpp>
#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
/*
   ˫Ŀ������ճ���
*/
int process(VideoCapture capture[])
{
	int n = 0;//������Ƭ��
	char filename[200];//�����ͼƬ·����
	string windowName = "TWOCam";//������
	cout << "Enter the space bar to save the picture.\n";
	Mat frame[2];//����ץȡ��֡���ݴ洢������������ͷ��
	for (;;)//����ѭ������ȡûһ֡������
	{
		capture[0] >> frame[0];//����ͷ0�������һ֡���뵽Mat[0]������
		waitKey(20);
		capture[1] >> frame[1];//����ͷ1�������һ֡���뵽Mat[1]������
		if (frame[0].empty()|| frame[1].empty())//�����õ�һ֡Ϊ���򷵻أ�����ץȡ
			break;
		transpose(frame[0], frame[0]);
		//flip(frame[0], frame[0], 1);
		imshow("Video0", frame[0]);
		//flip(frame[1],);
		transpose(frame[1], frame[1]);
		//flip(frame[1], frame[1], -1);//��ת��������ͷ�������⣬����flip����
		imshow("Video1", frame[1]);
		char key = (char)waitKey(70);//ÿ��ʾһ֡���ݵ�ʱ��ͣ70ms������Ƿ��°���
		switch (key)
		{
		case 'q':
		case 'Q':
		case 27: // escape
			return 0;
		case ' '://�ո����������Ϣ
			sprintf(filename, "imageLeft%.1d.jpg", n);
			imwrite(filename, frame[0]);
			cout << "Saved " << filename << endl;
			sprintf(filename, "imageRight%.1d.jpg", n++);
			imwrite(filename, frame[1]);
			cout << "Saved " << filename << endl;
			break;
		default:
			break;
		}
	}
	return 0;
}

int main()
{
	VideoCapture capture[2];
	capture[0].open(0);
	capture[1].open(1);
	if (!capture[0].isOpened())
	{
		cerr << "Failed to open the video device [0].\n";
		return 1;
	}
	if (!capture[1].isOpened())
	{
		cerr << "Failed to open the video device [1].\n";
		return 1;
	}
	return process(capture);
}
