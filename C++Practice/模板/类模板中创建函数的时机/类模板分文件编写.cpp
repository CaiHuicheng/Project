#include<iostream>
#include<string>
#include"person.hpp"
using namespace std;
//类模板的分文件编写问题和解决
//类模板中成员函数创建时机在调用阶段，导致分文件编写时链接不到

//1、直接包含.cpp源文件
//2、将声明和实现写到同一个文件中，并更改后缀名为.hpp
//hpp是约定的名称，并不是强制
//template<class T1, class T2>
//class Person
//{
//public:
//	Person(T1 name, T2 age);
//	void showPerson();
//	T1 m_Name;
//	T2 m_age;
//};
////构造函数的类外实现
//template<class T1, class T2>
//Person<T1, T2>::Person(T1 name, T2 age) {
//	this->m_Name = name;
//	this->m_age = age;
//}
////成员函数的类外实现
//template<class T1, class T2>
//void Person<T1, T2>::showPerson()
//{
//	cout << this->m_Name << this->m_age << endl;
//}
void test01() {
	Person<string, int> p("Tom", 19);
	p.showPerson();
}

int main() {
	test01();
	system("pause");
	return 0;
}