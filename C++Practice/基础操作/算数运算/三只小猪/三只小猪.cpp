#include<iostream>
using namespace std;

int main() {

	//��ֻС������أ��ж���ֻ����

	int num1 = 0, num2 = 0, num3 = 0;
	cout << "������С��A���أ�" << endl;
	cin >> num1;

	cout << "������С��B���أ�" << endl;
	cin >> num2;

	cout << "������С��C���أ�" << endl;
	cin >> num3;

	cout << "С��A������Ϊ��" << num1 << "kg" << endl;
	cout << "С��B������Ϊ��" << num2 << "kg" << endl;
	cout << "С��C������Ϊ��" << num3 << "kg" << endl;

	if (num1==num2&&num2==num3&&num1==num3)
	{
		cout << "��ֻһ����" << endl;
	}
	else {
		if (num1 > num2)
		{
			if (num1 > num3)
			{
				cout << "С��A����" << endl;
			}
			else
			{
				cout << "С��C����" << endl;
			}
		}
		else
		{
			if (num2 > num3)
			{
				cout << "С��B����" << endl;
			}
			cout << "С��C����" << endl;
		}
	}
	system("pause");
	return 0;
}