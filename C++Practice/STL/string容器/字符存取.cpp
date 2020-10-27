#include<iostream>
#include<string>
using namespace std;

//string 字符存取

void test01() {
	string str1 = "hello world";

	cout << "str1="<< str1 << endl;

	//通过[]访问单个字符
	for (int i = 0; i < str1.size(); i++)
	{
		cout << str1[i] << " ";
	}
	cout << endl;
	//通过 at()访问单个字符
	for (int i = 0; i < str1.size(); i++)
	{
		cout << str1.at(i) << " ";
	}
	cout << endl;

	//修改单个字符 []和at
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