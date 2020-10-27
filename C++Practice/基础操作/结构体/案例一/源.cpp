#include<iostream>
#include<string>
#include<time.h>
using namespace std;

//学生结构体
struct Student {
	//学生名字
	string sname;
	//学生成绩
	int score;
};
//老师结构体
struct Teacher {
	//老师名字
	string tname;
	//一个老师带五个学生
	struct Student sArray[5];
};

void allocateSpace(struct Teacher tArray[], int len) {
	string nameSeed = "ABCDE";
	//给老师信息赋值
	for (int i = 0; i < len; i++)
	{
		tArray[i].tname = "Teacher_";
		tArray[i].tname += nameSeed[i];
		for (int j = 0; j < 5; j++)
		{
			tArray[i].sArray[j].sname = "Studnet_";
			tArray[i].sArray[j].sname += nameSeed[j];
			int random = rand() % 61 + 40;//40~100
			tArray[i].sArray[j].score = random;

		}
	}
}

//打印所有信息
void printInfo(struct Teacher tArray[], int len) {
	for (int i = 0; i < len; i++)
	{
		cout << "老师姓名：" << tArray[i].tname << endl;
		for (int j = 0; j < 5; j++)
		{
			cout << "\t学生姓名：" << tArray[i].sArray[j].sname << "\t分数：" << tArray[i].sArray[j].score << endl;
		}
	}
}

int main() {
	//随机数种子
	srand((unsigned int)time(NULL));

	//1、创建3名老师的数组
	struct Teacher tArray[3];
	//2、通过函数给3位老师的信息赋值，并给老师的学生信息赋值
	int len = sizeof(tArray) / sizeof(tArray[0]);
	allocateSpace(tArray, len);
	//3、打印所有信息
	printInfo(tArray, len);
	system("pause");
	return 0;
}