#include<iostream>
#include<string>
using namespace std;
#include<set>

/*
	pair对组

	pair<type,type> p(value1,value2);
	pair<type,type> p = make_pair(value1,value2);
*/


//pair创建
void test01() {
	//创建方式一
	pair<string, int> p("Tom", 20);
	cout << "姓名：" << p.first << "年龄：" << p.second << endl;

	//创建方式二
	pair<string, int> p1 = make_pair("Jerry", 20);
	cout << "姓名：" << p1.first << "年龄：" << p1.second << endl;
}


int main() {
	test01();
	system("pause");
	return 0;
}