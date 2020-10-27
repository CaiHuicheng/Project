#include<iostream>
#include<string>
using namespace std;

//string的构造函数

void test01() {
	string s1;//默认构造
	const char * str = "hello World";
	string s2(str);

	cout << "s2 = " << s2 << endl;

	string s3(s2);

	cout << "s3 = " << s3 << endl;

	string s4(8, 'a');

	cout << "s4 = " << s4 << endl;

}

int main() {
	test01();
	system("pause");
	return 0;
}