#include<iostream>
#include<string>
using namespace std;
#include<set>

/*
	pair����

	pair<type,type> p(value1,value2);
	pair<type,type> p = make_pair(value1,value2);
*/


//pair����
void test01() {
	//������ʽһ
	pair<string, int> p("Tom", 20);
	cout << "������" << p.first << "���䣺" << p.second << endl;

	//������ʽ��
	pair<string, int> p1 = make_pair("Jerry", 20);
	cout << "������" << p1.first << "���䣺" << p1.second << endl;
}


int main() {
	test01();
	system("pause");
	return 0;
}