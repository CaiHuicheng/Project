#include<iostream>
#include<string>
using namespace std;

//string ¸³Öµ²Ù×÷

void test01() {
	string str1 = "hello world";

	str1 += "C++";

	str1 += ':';

	cout << "str1=" << str1 << endl;

	string str2="Ñ§Ï°£º";
	str2 += str1;
	cout << "str2=" << str2 << endl;

	string str4;
	str4.append("hello");
	cout << "str4=" << str4 << endl;
	str4.append("world!!!!", 6);
	cout << "str4=" << str4 << endl;
	str4.append(str2);
	cout << "str4=" << str4 << endl;
	str4.append(str2, 0, 6);
	cout << "str4=" << str4 << endl;
}

int main() {
	test01();
	system("pause");
	return 0;
}