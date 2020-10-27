#include<iostream>
#include<string>
using namespace std;

//通过全局函数 打印Person信息
//成员函数的类外实现
template<class T1, class T2>
//提前让编译器知道Person存在
class Person;
template<class T1, class T2>
void showPerson2(Person<T1, T2> p)
{
	cout << p.m_Name << p.m_age << endl;
}
template<class T1, class T2>
class Person
{
	//全局函数 类内实现
	friend void showPerson1(Person<T1, T2> p)
	{
		cout << p.m_Name << p.m_age << endl;
	}
	//全局函数 类外实现
	//加空模板参数列表
	//如果全局函数 提前知道
	friend void showPerson2<>(Person<T1, T2> p);
public:
	Person(T1 name, T2 age) {
		this->m_Name = name;
		this->m_age = age;
	}
private:
	T1 m_Name;
	T2 m_age;
};
void test01() {
	Person<string, int> p("Tom", 19);
	showPerson1(p);
}

void test02() {
	Person<string, int> p("Tom", 120);
	showPerson2(p);
}
int main() {
	test01();
	test02();
	system("pause");
	return 0;
}