#include<iostream>
#include<ctime>
using namespace std;
int main() {
	//1��ϵͳ��������� ע�����ʱ������
	srand((unsigned int)time(NULL));
	int num = rand() % 100 + 1;//1~100��ֵ
	//2����ҽ��в²�
	int val = 0;
	
	//3���ж���ҵĲ²�
	while (1)
	{
		cin >> val;
		if (val > num)
		{
			cout << "�²����" << endl;
		}
		else if (val < num)
		{
			cout << "�²��С" << endl;
		}
		else
		{
			cout << "��ϲ�¶���" << endl;
			break;
		}
	}
	return 0;
}