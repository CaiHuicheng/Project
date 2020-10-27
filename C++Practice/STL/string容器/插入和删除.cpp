#include<iostream>
#include<string>
using namespace std;

//string ×Ö·û´æÈ¡

void test01() {
	string str1 = "hello world";

	cout << "str1=" << str1 << endl;
	//²åÈë
	str1.insert(0, "C++:");

	cout << "str1=" << str1 << endl;

	//É¾³ý

	str1.erase(0, 3);
	cout << "str1=" << str1 << endl;
}

int main() {
	//test01();
	test01();
	system("pause");
	return 0;
}