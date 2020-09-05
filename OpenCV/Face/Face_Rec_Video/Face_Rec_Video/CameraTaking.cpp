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
		cascada.detectMultiScale(frame_gray, faces, 1.1, 4, CV_HAAR_DO_ROUGH_SEARCH, Size(70, 70), Size(1000, 1000));
		printf("��⵽����������%d\n", faces.size());
		//1.frame_gray��ʾ����Ҫ��������ͼ�� 2.faces��ʾ��⵽������Ŀ������,3. 1.1��ʾÿ��ͼ��ߴ��С�ı���
		//4. 4��ʾÿһ��Ŀ������Ҫ����⵽3�β��������Ŀ��(��Ϊ��Χ�����غͲ�ͬ�Ĵ��ڴ�С�����Լ�⵽������ʾÿһ��Ŀ������Ҫ����⵽3�β��������Ŀ��(��Ϊ��Χ�����غͲ�ͬ�Ĵ��ڴ�С�����Լ�⵽����
		/*5.flags�CҪôʹ��Ĭ��ֵ��Ҫôʹ��CV_HAAR_DO_CANNY_PRUNING��
		��������ʹ��Canny��Ե������ų���Ե�������ٵ�����
		��Ϊ��Щ����ͨ��������������������opencv3 �Ժ󶼲������������*/
		//6. Size(100, 100)ΪĿ�����С�ߴ� һ��Ϊ30*30 ����С���� Ҳ����
		//7. Size(500, 500)ΪĿ������ߴ� ��ʵ���Բ��������opencv���Զ�ȥ��������ߴ�
		//�ʵ�����5,6,7�����������������ų�������еĸ����
		//ʶ�𵽵����þ���Ȧ��
		for (int i = 0; i < faces.size(); i++)
		{
			rectangle(frame, faces[i], Scalar(255, 0, 0), 2, 8, 0);
		}
		//��ֻ��һ������ʱ����ʼ����
		int key;
		if ((key = waitKey(5)) != -1) {
			if (faces.size() == 1 && key == ' ')
			{
				Mat faceROI = frame_gray(faces[0]);//�ڻҶ�ͼ�н�Ȧ��������������ü���
												   //cout << faces[0].x << endl;//������face[0].x
				resize(faceROI, myFace, Size(92, 112));//����Ȥ��sizeΪ92*112
				putText(frame, to_string(pic_num), faces[0].tl(), 3, 1.2, (0, 0, 225), 2, 0);//�� faces[0].tl()�����Ͻ�����д���
				string filename = format("%d.jpg", pic_num); //����ڵ�ǰ��Ŀ�ļ�����1-10.jpg ������format����תΪ�ַ���
				imwrite(filename, myFace);//���ڵ�ǰĿ¼��
				imshow(filename, myFace);//��ʾ��size�����
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