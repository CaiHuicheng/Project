#include<iostream>
#include<string>
using namespace std;

//string �ַ���ȡ

void test01() {
	string str1 = "hello world";

	cout << "str1="<< str1 << endl;

	//ͨ��[]���ʵ����ַ�
	for (int i = 0; i < str1.size(); i++)
	{
		cout << str1[i] << " ";
	}
	cout << endl;
	//ͨ�� at()���ʵ����ַ�
	for (int i = 0; i < str1.size(); i++)
	{
		cout << str1.at(i) << " ";
	}
	cout << endl;

	//�޸ĵ����ַ� []��at
	str1[0] = 'H';
	str1.at(1) = 'H';
	cout << "str1=" << str1 << endl;
}

int main() {
	//test01();
	test01();
	system("pause");
	return 0;
}