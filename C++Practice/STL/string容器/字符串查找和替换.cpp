#include<iostream>
#include<string>
using namespace std;

//string 查找和替换

void test01() {
	string str1 = "hello world";
	//判断未找到字符串
	if (str1.find("o")==-1)
	{
		cout << "未找到指定字符串" << endl;
	}
	else
	{
		cout << "pos=" << str1.find("o") << endl;//返回“o”的下标
	}

	int pos = str1.rfind("o");//find从左往右找  rfind 从右往左找

	cout << "pos=" << pos << endl;//返回“o”的下标
	
}

void test02() {
	string str1 = "abcdefg";
	str1.replace(1, 3, "1111");
	cout << "str1=" << str1 << endl;
}

int main() {
	//test01();
	test02();
	system("pause");
	return 0;
}