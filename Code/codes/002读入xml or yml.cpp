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

student_t st[3];

//打印出学生资料，来验证读取文件信息是否成功
void stu_info_dump()
{
	for (int i = 0; i < 3; i++)
	{
		printf("第%d个学生\n",i+1);
		cout << "name:" << st[i].name << endl;
		cout << "id:" << st[i].id << endl;
		cout << "age:" << st[i].age << endl;
		cout << "contact address:" << st[i].contact_ways.address << endl;
		cout << "contact number:" << st[i].contact_ways.phone_num << endl;
		cout << "father name:" << st[i].parents[0].name << endl;
		cout << "father age:" << st[i].parents[0].age << endl;
		cout << "mother name:" << st[i].parents[1].name << endl;
		cout << "mother age:" << st[i].parents[1].age << endl;
		printf("\n\n");
	}
}

int main(int argc, char** argv)
{

	FileStorage fs("student.xml", FileStorage::READ); //填入读操作

	memset(st, 0, sizeof(st));

	FileNode student_node = fs["student"];//读取根节点
	FileNodeIterator fni = student_node.begin(); //获取结构体数组迭代器
	FileNodeIterator fniEnd = student_node.end();
	int count = 0;
	for (; fni != fniEnd; fni++)//遍历  
	{

		st[count].name = (string)(*fni)["name"];
		st[count].id = (int)(*fni)["id"];
		st[count].age = (int)(*fni)["age"];
	
		//contact结构体内容
		FileNode contact = (*fni)["contact_ways"];
		st[count].contact_ways.address = (string)contact["address"];
		st[count].contact_ways.phone_num = (string)contact["phone_number"];

		//parents结构体数组内容
		FileNode parents = (*fni)["parents"];
		FileNodeIterator fni2 = parents.begin(); //获取结构体数组迭代器
		FileNodeIterator fniEnd2 = parents.end();
		int count2 = 0;
		for (; fni2 != fniEnd2; fni2++)//遍历  
		{
			st[count].parents[count2].name = (string)(*fni2)["name"];
			st[count].parents[count2].age = (int)(*fni2)["age"];
			count2++;
		}

		count++;
	}


	stu_info_dump();

	return 0;
}