#include<iostream>
#include<string>
using namespace std;

//string ��ֵ����

void test01() {
	string str1;
	str1 = "hello world";
	cout << "str1=" << str1 << endl;

	string str2;
	str2 = str1;
	cout << "str2=" << str2 << endl;

	string str4;
	str4.assign("hello");
	cout << "str4=" << str4 << endl;

	string str5;
	str5.assign(str2, 3);
	cout << "str5=" << str5 << endl;

	string str6;
	str6.assign(str1);
	cout << "str6=" << str6 << endl;

	string str7;
	str7.assign(10, '2');
	cout << "str7=" << str7 << endl;
}

int main() {
	test01();
	system("pause");
	return 0;
}