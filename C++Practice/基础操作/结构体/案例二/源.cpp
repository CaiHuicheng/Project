#include<iostream>
#include<string>
using namespace std;

struct Hero {
	//����
	string name;
	//����
	int age;
	//�Ա�
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
		cout << "����:" << heroArray[i].name << "\t����:" << heroArray[i].age << "\t�Ա�:" << heroArray[i].sex << endl;
	}
}

int main() {
	//1�����Ӣ�۽ṹ��
	
	//2������������5��Ӣ��

	struct Hero heroArray[5] = {
		{"����",24,"��"},
		{"����",22,"��"},
		{"�ŷ�",20,"��"},
		{"����",21,"��"},
		{"����",19,"Ů"}
	};
	int len = sizeof(heroArray) / sizeof(heroArray[0]);
	/*for (int i = 0; i < len; i++)
	{
		cout << "����:" << heroArray[i].name << "\t����:" << heroArray[i].age << "\t�Ա�:" << heroArray[i].sex << endl;
	}
*/
	//3��������������򣬰��������С����
	bubbleSort(heroArray, len);

	//4����ӡ���

	printInfo(heroArray, len);

	system("pause");
	return 0;
}