#include<iostream>
#include<string>
using namespace std;

//string 比较操作

void test01() {
	string str1 = "hello world";
	
	string str2 = "hello xorld";

	if (str1.compare(str2)==0)
	{
		cout << "str1等于str2" << endl;
	}
	else if (str1.compare(str2)>0)
	{
		cout << "str1大于str2" << endl;
	}
	else
	{
		cout << "str1小于str2" << endl;
	}
}

int main() {
	//test01();
	test01();
	system("pause");
	return 0;
}