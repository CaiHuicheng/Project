#include<opencv2\opencv.hpp>   
#include<opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

typedef struct
{
	string phone_num;
	string address;
}contact_t;

typedef struct
{
	string name;
	int age;
}parents_t;

typedef struct
{
	string name;
	int age;
	int id;
	contact_t contact_ways;
	parents_t parents[2];
}student_t;

int main(int argc, char** argv)
{

	FileStorage fs("student.xml", FileStorage::WRITE); //填入写操作

	student_t st[3]; 
	memset(st, 0, sizeof(st));

	//测试数据填入
	st[0].name = "Kobe";
	st[0].age = 21;
	st[0].id = 1;
	st[0].contact_ways.address = "1st building";
	st[0].contact_ways.phone_num = "123";
	st[0].parents[0].name = "dad";
	st[0].parents[1].name = "mum";
	st[0].parents[0].age = 40;
	st[0].parents[1].age = 39;

	st[1].name = "James";
	st[1].age = 20;
	st[1].id = 2;
	st[1].contact_ways.address = "2st building";
	st[1].contact_ways.phone_num = "12223";
	st[1].parents[0].name = "daddy";
	st[1].parents[1].name = "mumy";
	st[1].parents[0].age = 44;
	st[1].parents[1].age = 38;


	fs << "student" << "["; //结构体数组的开始
	for (int i = 0; i < 3; i++)
	{
		fs <<"{"; //结构体的开始
		fs << "name" << st[i].name;
		fs << "age" << st[i].age;
		fs << "id" << st[i].id;

		fs << "contact_ways" << "{";  //嵌套结构体的开始
		fs << "phone_number" << st[i].contact_ways.phone_num;
		fs << "address" << st[i].contact_ways.address;
		fs << "}";  //结构体结束

		fs << "parents"<<"[";  //嵌套结构体数组开始
		for (int j = 0; j < 2; j++)
		{
			fs << "{";
			fs << "name" << st[i].parents[j].name;
			fs << "age" << st[i].parents[j].age;
			fs << "}";
		}
		fs << "]";  //嵌套结构体数组结束

		fs << "}"; //结构体结束

	}
	fs << "]"; // 结构体数组结束

	return 0;
}