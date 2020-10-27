#include<iostream>
#include<string>
using namespace std;
//类模板与函数模板的区别
//1、类模板没有自动类型推导的使用方式
//2、类模板在模板参数列表中可以有默认参数

template <class NameType, class AgeType = int>//class AgeType = int 模板参数列表中可以有默认参数
class Person
{
public:
	Person(NameType name, AgeType age ) {
		this->m_Name = name;
		this->m_Age = age;
	}
	void showPerson() {
		cout << "name:" << this->m_Name << endl;
		cout << "age:" << this->m_Age << endl;
	}
	string m_Name;
	int m_Age;
};
//1、类模板没有自动类型推导的使用方式
void test01() {
	//Person p1("虽无看", 999); //无法用自动推导
	Person<string, int> p1("虽无看", 999);
	p1.showPerson();

}
//2、类模板在模板参数列表中可以有默认参数
void test02() {
	Person<string> p2("猪八戒", 333);
	p2.showPerson();
}
int main() {

	test02();
	system("pause");
	return 0;
}