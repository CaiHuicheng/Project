#include<iostream>
using namespace std;
//�������壺1�� #define �������ļ��Ϸ�     2���� ����ǰ��ӹؼ���const
//���������﷨���������� ������ = ����ֵ;
constexpr auto Day = 7;

int main() {
	//DayΪ�����޸Ļᱨ��,const���ε�Ҳ�ǳ���

	const int month = 12;

	cout << "һ��һ����" << Day <<"��"<< endl;
	cout << "һ��һ����" << month << "��" << endl;

	system("pause");

	return 0;
}