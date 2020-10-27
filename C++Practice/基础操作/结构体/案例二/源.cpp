#include<iostream>
#include<string>
using namespace std;

struct Hero {
	//姓名
	string name;
	//年龄
	int age;
	//性别
	string sex;
};

void bubbleSort(struct Hero heroArray[], int len) {
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i - 1; j++) {
			if (heroArray[j].age > heroArray[j + 1].age) {
				struct Hero temp = heroArray[j];
				heroArray[j] = heroArray[j + 1];
				heroArray[j + 1] = temp;
			}
		}

	}
}

void printInfo(struct Hero heroArray[], int  len) {
	for (int i = 0; i < len; i++)
	{
		cout << "姓名:" << heroArray[i].name << "\t年龄:" << heroArray[i].age << "\t性别:" << heroArray[i].sex << endl;
	}
}

int main() {
	//1、设计英雄结构体
	
	//2、创建数组存放5名英雄

	struct Hero heroArray[5] = {
		{"刘备",24,"男"},
		{"关羽",22,"男"},
		{"张飞",20,"男"},
		{"赵云",21,"男"},
		{"貂蝉",19,"女"}
	};
	int len = sizeof(heroArray) / sizeof(heroArray[0]);
	/*for (int i = 0; i < len; i++)
	{
		cout << "姓名:" << heroArray[i].name << "\t年龄:" << heroArray[i].age << "\t性别:" << heroArray[i].sex << endl;
	}
*/
	//3、对数组进行排序，按照年龄从小到大
	bubbleSort(heroArray, len);

	//4、打印输出

	printInfo(heroArray, len);

	system("pause");
	return 0;
}