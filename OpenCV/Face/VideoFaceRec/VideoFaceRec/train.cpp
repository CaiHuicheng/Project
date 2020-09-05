#include<opencv2\face\facerec.hpp> 
#include<opencv2\core.hpp>
#include<opencv2\face.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>

#include <math.h>  
#include <iostream>  
#include <fstream>  
#include <sstream>  


using namespace cv;
using namespace cv::face;
using namespace std;

static Mat norm_0_255(InputArray _src) {
	Mat src = _src.getMat();
	// �����ͷ���һ����һ�����ͼ�����:  
	Mat dst;
	switch (src.channels()) {
	case 1:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
		break;
	case 3:
		cv::normalize(_src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
		break;
	default:
		src.copyTo(dst);
		break;
	}
	return dst;
}

//ʹ��CSV�ļ�ȥ��ͼ��ͱ�ǩ����Ҫʹ��stringstream��getline����  
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
	std::ifstream file(filename.c_str(), ifstream::in);//c_str()�������ÿɲ��ã����践��һ����׼C���͵��ַ���
	if (!file)
	{
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) //���ı��ļ��ж�ȡһ���ַ���δָ���޶���Ĭ���޶���Ϊ��/n��
	{
		stringstream liness(line);//�������stringstream��Ҫ���������ַ����ķָ�
		getline(liness, path, separator);//����ͼƬ�ļ�·���Էֺ���Ϊ�޶���
		getline(liness, classlabel);//����ͼƬ��ǩ��Ĭ���޶���
		if (!path.empty() && !classlabel.empty()) //�����ȡ�ɹ�����ͼƬ�Ͷ�Ӧ��ǩѹ���Ӧ������
		{
			images.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}

int main()
{
	//��ȡ���CSV�ļ�·��.  
	//string fn_csv = string(argv[1]);  
	string fn_csv = "face.txt";

	// 2�����������ͼ�����ݺͶ�Ӧ�ı�ǩ  
	vector<Mat> images;
	vector<int> labels;
	try
	{
		read_csv(fn_csv, images, labels); //��csv�ļ���������ȡѵ������
	}
	catch (cv::Exception& e)
	{
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		// �ļ������⣬�˳�  
		exit(1);
	}
	// ���û�ж�ȡ���㹻ͼƬ��Ҳ�˳�.  
	if (images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
	}

	for (int i = 0; i < images.size(); i++)
	{
		if (images[i].size() != Size(92, 112))
		{
			cout << i << endl;
			cout << images[i].size() << endl;
		}
	}


	// ����ļ��д�������Ǵ�������ݼ����Ƴ����һ��ͼƬ����Ϊ����ͼƬ  
	//[gm:��Ȼ������Ҫ�����Լ�����Ҫ�޸ģ���������˺ܶ�����]  
	Mat testSample = images[images.size() - 1];
	int testLabel = labels[labels.size() - 1];
	images.pop_back();//ɾ�����һ����Ƭ������Ƭ��Ϊ����ͼƬ
	labels.pop_back();//ɾ������һ����Ƭ��labels
	// ���漸�д�����һ��������ģ����������ʶ��  
	// ͨ��CSV�ļ���ȡ��ͼ��ͱ�ǩѵ������  
	// T������һ��������PCA�任  
	//�����ֻ�뱣��10�����ɷ֣�ʹ�����´���  
	//      cv::createEigenFaceRecognizer(10);  
	//  
	// ����㻹ϣ��ʹ�����Ŷ���ֵ����ʼ����ʹ��������䣺  
	//      cv::createEigenFaceRecognizer(10, 123.0);  
	//  
	// �����ʹ��������������ʹ��һ����ֵ��ʹ��������䣺  
	//      cv::createEigenFaceRecognizer(0, 123.0);  

	//����һ��PCA��������������ʱ����Ϊmodel�ɣ�������ɺ�
	//�������еĳ�Ա����train()����ɷ�������ѵ��
	Ptr<BasicFaceRecognizer> model = EigenFaceRecognizer::create();
	model->train(images, labels);
	model->save("MyFacePCAModel.xml");//����·�����Լ����ã���ע���á�\\��

	Ptr<BasicFaceRecognizer> model1 = FisherFaceRecognizer::create();
	model1->train(images, labels);
	model1->save("MyFaceFisherModel.xml");

	Ptr<LBPHFaceRecognizer> model2 = LBPHFaceRecognizer::create();
	model2->train(images, labels);
	model2->save("MyFaceLBPHModel.xml");

	// ����Բ���ͼ�����Ԥ�⣬predictedLabel��Ԥ���ǩ���  
	//ע��predict()��ڲ�������Ϊ��ͨ���Ҷ�ͼ�����ͼ�����Ͳ�������Ҫ�Ƚ���ת��
	//predict()��������һ�����α�����Ϊʶ���ǩ
	int predictedLabel = model->predict(testSample);//���ط�����
	int predictedLabel1 = model1->predict(testSample);
	int predictedLabel2 = model2->predict(testSample);

	// ����һ�ֵ��÷�ʽ�����Ի�ȡ���ͬʱ�õ���ֵ:  
	// int predictedLabel = -1;  
	// double confidence = 0.0;  
	//  model->predict(testSample, predictedLabel, confidence);  

	string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
	string result_message1 = format("Predicted class = %d / Actual class = %d.", predictedLabel1, testLabel);
	string result_message2 = format("Predicted class = %d / Actual class = %d.", predictedLabel2, testLabel);
	cout << result_message << endl;
	cout << result_message1 << endl;
	cout << result_message2 << endl;

	getchar();
	//waitKey(0);
	return 0;
}