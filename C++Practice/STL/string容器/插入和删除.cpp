#include<iostream>
#include<string>
using namespace std;

//string �ַ���ȡ

void test01() {
	string str1 = "hello world";

	cout << "str1=" << str1 << endl;
	//����
	str1.insert(0, "C++:");

	cout << "str1=" << str1 << endl;

	//ɾ��

	str1.erase(0, 3);
	cout << "str1=" << str1 << endl;
}

int main() {
	//test01();
	test01();
	system("pause");
	return 0;
}