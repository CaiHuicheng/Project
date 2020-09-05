#include<opencv2\opencv.hpp>  
#include<opencv2\face.hpp>
#include<opencv2\core\core.hpp>
#include<opencv2\face\facerec.hpp>
#include <fstream>  
#include <sstream> 
#include<math.h>

using namespace std;
using namespace cv;
using namespace cv::face;

RNG g_rng(12345);
Ptr<FaceRecognizer> model;

int Predict(Mat src_image)  //ʶ��ͼƬ
{
	Mat face_test;
	int predict = 0;
	//��ȡ��ROI�����ߴ����
	if (src_image.rows >= 120)
	{
		//�ı�ͼ���С��ʹ��˫���Բ�ֵ
		resize(src_image, face_test, Size(92, 112));

	}
	//�ж��Ƿ���ȷ���ROI
	if (!face_test.empty())
	{
		//����ͼ��Ӧ���ǻҶ�ͼ  
		predict = model->predict(face_test);
	}
	cout << predict << endl;
	return predict;
}
int main()
{
	VideoCapture cap(0);    //��Ĭ������ͷ  
	if (!cap.isOpened())
	{
		return -1;
	}
	Mat frame;
	Mat gray;
	//����������������������
	CascadeClassifier cascade;
	bool stop = false;
	//ѵ���õ��ļ����ƣ������ڿ�ִ���ļ�ͬĿ¼��  
	cascade.load("haarcascade_frontalface_alt2.xml");

	model = FisherFaceRecognizer::create();
	//����ѵ���õķ�����
	model->read("MyFacePcaModel.xml");
	//��������ͷ�ɼ�������ʶ��
	while (1)
	{
		cap >> frame;

		vector<Rect> faces(0);//�������ڴ����������������

		cvtColor(frame, gray, CV_RGB2GRAY);//����ͼ�����Ϊ�Ҷ�ͼ

		equalizeHist(gray, gray); //�任���ͼ�����ֱ��ͼ��ֵ������  
		//�������
		cascade.detectMultiScale(gray, faces,
			1.1, 4, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT  
			| CV_HAAR_DO_ROUGH_SEARCH,
			//| CV_HAAR_SCALE_IMAGE,
			Size(30, 30), Size(500, 500));
		Mat* pImage_roi = new Mat[faces.size()];    //��������
		Mat face;
		Point text_lb;//�ı�д�ڵ�λ��
		//�������
		string str;
		for (int i = 0; i < faces.size(); i++)
		{
			pImage_roi[i] = gray(faces[i]); //�����е�������������
			text_lb = Point(faces[i].x, faces[i].y);
			if (pImage_roi[i].empty())
				continue;
			switch (Predict(pImage_roi[i])) //��ÿ������ʶ��
			{
			case 41:str = "С��"; break;
			default: str = "Error"; break;
			}
			Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//��ȡ����ɫ����ֵ
			rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), color, 1, 8);//���뻺��
			putText(frame, str, text_lb, FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255));//�������
		}

		delete[]pImage_roi;
		imshow("face", frame);
		waitKey(200);
	}

	return 0;
}