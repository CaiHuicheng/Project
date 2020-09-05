//face_recog_from_video.cpp �������̨Ӧ�ó������ڵ㡣

// train_PCA_model.cpp  
//����ѵ������ʶ�������pCAģ��  
#include"opencv2/opencv.hpp"
#include"opencv2/core.hpp"
#include"opencv2/imgproc.hpp"
#include"opencv2/highgui.hpp"
#include"opencv2/face.hpp"  // ����FaceRecognizer
#include<iostream>

using namespace std;
using namespace cv;
using namespace cv::face;


static  void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, int max, int min, char separator);
int CountMax = 9, CountMin = 0;


int  main(int argc, char *argv[])
{
	string csvFile = "face.txt";
	vector<Mat> images;
	vector<int> labels;


	// ��ȡcsv�ļ�  
	try
	{
		read_csv(csvFile, images, labels, CountMax, CountMin, ';'); //��ȡcsvFile�����е�img��label  
	}
	catch (cv::Exception& e) // �쳣���  
	{                  // cerr���������׼�����ostream���󣬳����ڳ��������Ϣ  
		cerr << "Error opening file\" " << csvFile << "\".reason: " << e.msg << endl; //�쳣 ������ԭ��  
		exit(-1);
	}


	// ��δ��ȡ���㹻ͼƬ��Ҳ�˳�  
	if (images.size() <= 1)
	{
		string errMsg = "THis demo needs at least 2 images to work.please add images!";
		CV_Error(CV_StsError, errMsg);

	}
	cout << "train1.��ȡok" << endl;

	// ѵ�����ݣ�����ѵ���õ�����ģ�ͱ��浽.xml��  
	// Ptr<>Ϊģ���࣬����modelΪָ��FaceRecognizer���ָ�롣modelΪָ�룡    
	//	Ptr<EigenFaceRecognizer> model= EigenFaceRecognizer::create();// createEigenFaceRecognizer(20); // ����������ģ�� 20�����ɷ���   EigenFaceRecognizer::create();//  
	Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
	model->train(images, labels); //ѵ��  
	model->save("MyFacePcaModel.xml"); //��ѵ��ģ�ͱ��浽MyFacePcaModel.xml  

	cout << "train2.������ģ��ok" << endl;
	return 0;

}


/*
����:static void read_csv(const string& filename,vector<Mat>images, vector<int> labels,int CountMax,int CountMin, char separator=';')
���ܣ���ȡcsv�ļ���ͼ��·���ͱ�ǩ����Ҫʹ��stringstream��getline()
����˵����filename--Ҫ��ȡ��csv�ļ�
images----��ȡ��ͼƬ��������
labels----��ȡ��ͼƬ��Ӧ��ǩ ��������
CountMax,int CountMin--��ȡ��ÿһ����ͼƬ�±�����ֵ����Сֵ��Ĭ��ÿ�����10����Ƭ��
separator-�ָ���������ƶ�ȡ�����á����Զ���Ϊ���ſո�ȣ����˳����У�Ĭ��Ϊ�ֺ�
����ֵ����
*/
/*
��ע���������ڲ��漰���Ĳ�����ͷ���˵����
1. stringstream:�ַ�������
���ܣ����ڴ��еĶ��������󶨡�
2. getline():
����ԭ�ͣ�istream &getline( ifstream &input,string &out,char dielm)
����˵����Input--�����ļ�
out----����ַ���
dielm--��ȡ�����ַ�ֹͣ���𵽿������ã���Ĭ���ǻ��з���\n��
���ܣ� ��ȡ�ļ�Input�е��ַ�����out�С�
����ֵ������Input�������ļ�ĩβ�᷵���ļ�β����ʶeof
3. ifstream: ��Ӳ�̴��ļ�����ȡ�����Ӵ��������ļ��������ڴ���
ofstream: ���ڴ���ļ�����ȡ�������ڴ������ļ������������У�
*/
static  void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, int max, int min, char separator)
{
	std::ifstream  file(filename.c_str(), ifstream::in); // ��inģʽ����ȡ�ļ�ģʽ�����ļ� ,ʵ���ǽ�filename�ļ������� ��file 

	if (!file)
	{
		string error_message = "No valid input file was given,please check the given filename";
		CV_Error(CV_StsBadArg, error_message);

	}
	int ii = 0;

	/**********************��ȡ�ļ�.txt����****************************/
	string line, path, label;
	// [1]��ȡfile�ļ��е�һ���ַ����� line  
	while (getline(file, line, '\n'))  // ���ƣ�ֱ������file�ļ�ĩβ��eof��ʶ����������while  
	{
		// [2]��line�����ַ�����ȡ��lines(��)��  
		stringstream lines(line); //����->lines��������ȡ�ַ�ʱ��ָ���������������line��string���̶��ģ������еĶ�ȡÿ�ζ��Ǵ�lineͷ��ʼ  
								  // [3]��ȡ�ļ��е�·���ͱ�ǩ  
		getline(lines, path, separator); //��ʱ������ߵ�path֮���λ�ã������ֺŴ���  
		getline(lines, label);
		// [4]��ͼƬ�ͱ�ǩ����imgs �� labels  
		if ((path.empty() == 0) && (label.empty() == 0))
		{
			if (ii % 10 <= max && ii % 10 >= min)  //Ĭ��ÿ�����10����Ƭ  
			{
				Mat img = imread(path, 0);  //�ڶ�������Ϊ0 !!!  
											//Mat img = imread(ImageFileAddress, CV_LOAD_IMAGE_GRAYSCALE)��CV_LOAD_IMAGE_GRAYSCALEֵΪ 0��ָ��ͼ��ԭ��Ϊ��CV_LOAD_IMAGE_UNCHANGED����  
				if (img.data != 0)
				{
					images.push_back(img); // ��ͼƬ ��ӵ�images��  
					labels.push_back(atoi(label.c_str()));
				}
			}
			if (ii<9) ii++;
			else ii = 0;

		}
	}
}