#include<iostream>
#include<string>
using namespace std;

//string Çó×Ó´®

void test01() {
	string str1 = "hello world";
	
	string subString = str1.substr(1, 3);
	cout << "subString=" << subString << endl;
}

int main() {
	//test01();
	test01();
	system("pause");
	return 0;
}