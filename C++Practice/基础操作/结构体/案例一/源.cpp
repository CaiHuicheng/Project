#include<iostream>
#include<string>
#include<time.h>
using namespace std;

//ѧ���ṹ��
struct Student {
	//ѧ������
	string sname;
	//ѧ���ɼ�
	int score;
};
//��ʦ�ṹ��
struct Teacher {
	//��ʦ����
	string tname;
	//һ����ʦ�����ѧ��
	struct Student sArray[5];
};

void allocateSpace(struct Teacher tArray[], int len) {
	string nameSeed = "ABCDE";
	//����ʦ��Ϣ��ֵ
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

//��ӡ������Ϣ
void printInfo(struct Teacher tArray[], int len) {
	for (int i = 0; i < len; i++)
	{
		cout << "��ʦ������" << tArray[i].tname << endl;
		for (int j = 0; j < 5; j++)
		{
			cout << "\tѧ��������" << tArray[i].sArray[j].sname << "\t������" << tArray[i].sArray[j].score << endl;
		}
	}
}

int main() {
	//���������
	srand((unsigned int)time(NULL));

	//1������3����ʦ������
	struct Teacher tArray[3];
	//2��ͨ��������3λ��ʦ����Ϣ��ֵ��������ʦ��ѧ����Ϣ��ֵ
	int len = sizeof(tArray) / sizeof(tArray[0]);
	allocateSpace(tArray, len);
	//3����ӡ������Ϣ
	printInfo(tArray, len);
	system("pause");
	return 0;
}