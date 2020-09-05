//face_recog_from_video.cpp 定义控制台应用程序的入口点。

// train_PCA_model.cpp  
//用于训练人脸识别所需的pCA模型  
#include"opencv2/opencv.hpp"
#include"opencv2/core.hpp"
#include"opencv2/imgproc.hpp"
#include"opencv2/highgui.hpp"
#include"opencv2/face.hpp"  // 包含FaceRecognizer
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


	// 读取csv文件  
	try
	{
		read_csv(csvFile, images, labels, CountMax, CountMin, ';'); //读取csvFile中所有的img和label  
	}
	catch (cv::Exception& e) // 异常检查  
	{                  // cerr：输出到标准错误的ostream对象，常用于程序错误信息  
		cerr << "Error opening file\" " << csvFile << "\".reason: " << e.msg << endl; //异常 发生的原因  
		exit(-1);
	}


	// 若未读取到足够图片，也退出  
	if (images.size() <= 1)
	{
		string errMsg = "THis demo needs at least 2 images to work.please add images!";
		CV_Error(CV_StsError, errMsg);

	}
	cout << "train1.读取ok" << endl;

	// 训练数据，并将训练好的人脸模型保存到.xml中  
	// Ptr<>为模板类，定义model为指向FaceRecognizer类的指针。model为指针！    
	//	Ptr<EigenFaceRecognizer> model= EigenFaceRecognizer::create();// createEigenFaceRecognizer(20); // 创建特征脸模型 20张主成分脸   EigenFaceRecognizer::create();//  
	Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();
	model->train(images, labels); //训练  
	model->save("MyFacePcaModel.xml"); //将训练模型保存到MyFacePcaModel.xml  

	cout << "train2.创建脸模型ok" << endl;
	return 0;

}


/*
函数:static void read_csv(const string& filename,vector<Mat>images, vector<int> labels,int CountMax,int CountMin, char separator=';')
功能：读取csv文件的图像路径和标签。主要使用stringstream和getline()
参数说明：filename--要读取的csv文件
images----读取的图片（向量）
labels----读取的图片对应标签 （向量）
CountMax,int CountMin--读取的每一类别的图片下标的最大值和最小值（默认每个类别共10张照片）
separator-分隔符，起控制读取的作用。可自定义为逗号空格等，（此程序中）默认为分号
返回值：空
*/
/*
备注：（函数内部涉及到的部分类和方法说明）
1. stringstream:字符串流。
功能：将内存中的对象与流绑定。
2. getline():
函数原型：istream &getline( ifstream &input,string &out,char dielm)
参数说明：Input--输入文件
out----输出字符串
dielm--读取到该字符停止（起到控制作用），默认是换行符‘\n’
功能： 读取文件Input中的字符串到out中。
返回值：返回Input，若是文件末尾会返回文件尾部标识eof
3. ifstream: 从硬盘打开文件（读取），从磁盘输入文件，读到内存中
ofstream: 从内存打开文件（读取），从内存输入文件，读到磁盘中）
*/
static  void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, int max, int min, char separator)
{
	std::ifstream  file(filename.c_str(), ifstream::in); // 以in模式（读取文件模式）打开文件 ,实际是将filename文件关联给 流file 

	if (!file)
	{
		string error_message = "No valid input file was given,please check the given filename";
		CV_Error(CV_StsBadArg, error_message);

	}
	int ii = 0;

	/**********************读取文件.txt内容****************************/
	string line, path, label;
	// [1]读取file文件中的一行字符串给 line  
	while (getline(file, line, '\n'))  // 控制：直到读到file文件末尾（eof标识），才跳出while  
	{
		// [2]将line整行字符串读取到lines(流)中  
		stringstream lines(line); //区别->lines是流，读取字符时，指针会随流而动；而line是string，固定的，下文中的读取每次都是从line头开始  
								  // [3]读取文件中的路径和标签  
		getline(lines, path, separator); //此时光标已走到path之后的位置（即；分号处）  
		getline(lines, label);
		// [4]将图片和标签加入imgs 和 labels  
		if ((path.empty() == 0) && (label.empty() == 0))
		{
			if (ii % 10 <= max && ii % 10 >= min)  //默认每个类别共10张照片  
			{
				Mat img = imread(path, 0);  //第二个参数为0 !!!  
											//Mat img = imread(ImageFileAddress, CV_LOAD_IMAGE_GRAYSCALE)，CV_LOAD_IMAGE_GRAYSCALE值为 0，指灰图（原本为“CV_LOAD_IMAGE_UNCHANGED”）  
				if (img.data != 0)
				{
					images.push_back(img); // 将图片 添加到images中  
					labels.push_back(atoi(label.c_str()));
				}
			}
			if (ii<9) ii++;
			else ii = 0;

		}
	}
}