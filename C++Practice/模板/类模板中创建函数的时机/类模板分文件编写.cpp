#include<iostream>
#include<string>
#include"person.hpp"
using namespace std;
//��ģ��ķ��ļ���д����ͽ��
//��ģ���г�Ա��������ʱ���ڵ��ý׶Σ����·��ļ���дʱ���Ӳ���

//1��ֱ�Ӱ���.cppԴ�ļ�
//2����������ʵ��д��ͬһ���ļ��У������ĺ�׺��Ϊ.hpp
//hpp��Լ�������ƣ�������ǿ��
//template<class T1, class T2>
//class Person
//{
//public:
//	Person(T1 name, T2 age);
//	void showPerson();
//	T1 m_Name;
//	T2 m_age;
//};
////���캯��������ʵ��
//template<class T1, class T2>
//Person<T1, T2>::Person(T1 name, T2 age) {
//	this->m_Name = name;
//	this->m_age = age;
//}
////��Ա����������ʵ��
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