#include<opencv2\opencv.hpp>   
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

typedef struct
{
	int x;
	int y;
	string s;
}test_t;


int main(int argc, char** argv)
{
	FileStorage fs("test.xml", FileStorage::WRITE); //填入写操作

	//测试数据
	int a1 = 2;
	char a2 = -1;
	string str = "hello sysu!";
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	test_t t = { 3,4,"hi sysu" };
	map<string, int> m;
	m["kobe"] = 100;
	m["james"] = 99;
	m["curry"] = 98;

	//写入文件操作,先写标注在写数据
	fs << "int_data" << a1;
	fs << "char_data" << a2;
	fs << "string_data" << str;

	//写入数组
	fs <<"array_data"<< "["; //数组开始
	for (int i = 0; i < 10; i++)
	{
		fs << arr[i];
	}
	fs << "]"; //数组结束

	//写入结构体
	fs << "struct_data" << "{"; //结构体开始
	fs << "x" << t.x;
	fs << "y" << t.y;
	fs << "s" << t.s;
	fs << "}";  //结构结束


	//map的写入 
	fs << "map_data" << "{";  //map的开始写入
	map<string, int>::iterator it = m.begin();
	for (; it != m.end(); it++)
	{
		fs << it->first << it->second;
	}
	fs << "}";  //map写入结束


	return 0;
}