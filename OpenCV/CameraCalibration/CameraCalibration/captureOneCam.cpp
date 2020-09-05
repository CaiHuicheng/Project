#include <opencv2\imgcodecs.hpp>
#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
/*
   ��������ճ���
*/
int process(VideoCapture& capture)
{
	int n = 0;//������Ƭ��
	char filename[200];//�����ͼƬ·����
	string windowName = "camera_0";//������
	cout << "Enter the space bar to save the picture.\n";
	Mat frame;
	for (;;)//����ѭ������ȡûһ֡������
	{
		capture >> frame;//�������һ֡���뵽Mat������
		if (frame.empty())//�����õ�һ֡Ϊ���򷵻أ�����ץȡ
			break;
		imshow(windowName, frame);//��ʾ���ץȡ�Ĵ���
		char key = (char)waitKey(30);//ÿ��ʾһ֡���ݵ�ʱ��ͣ30ms������Ƿ��°���
		switch (key) 
		{
		case 'q':
		case 'Q':
		case 27: // escape
			return 0;
		case ' '://�ո����������Ϣ
			sprintf_s(filename, "0%.1d.png", n++);
			imwrite(filename, frame);//��ץ�ĵ�ͼƬ������
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
	VideoCapture capture(0);//�����������Ƶץȡ��0���豸��һ��Ϊ�ʼǱ��������
	if (!capture.isOpened())//�ж�����Ƿ���
	{
		cerr << "No camera detected.\n";
		return 1;
	}
	return process(capture);
}
