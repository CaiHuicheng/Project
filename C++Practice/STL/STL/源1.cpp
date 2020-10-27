#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//vectorr容器存放自定义数据类型
class Person
{
public:
	Person(string name,int age) {
		this->m_Name = name;
		this->Age = age;
	}
		string m_Name;
		int Age;
		
};

void myPrint(Person val) {
	cout << (val).m_Name << endl;
	cout << (val).Age << endl;
}
void test01() {
	//创建了一个vector容器
	vector<Person> v;
	//插入数据
	Person p1("aa", 10);
	Person p2("aa", 20);
	Person p3("aa", 30);
	Person p4("aa", 40);
	Person p5("aa", 50);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);
	//通过迭代器访问
	vector<Person>::iterator itbegin = v.begin();//起始迭代器 指向容器中第一个元素
	vector<Person>::iterator itend = v.end();//结束迭代器 指向容器中最后一个元素的下一个

	//1、遍历方式1 while
	while (itbegin != itend)
	{
		cout << (*itbegin).m_Name << endl;
		cout << (*itbegin).Age << endl;
		itbegin++;
	}
	//2、遍历方式2 for
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it).m_Name << endl;
		cout << (*it).Age << endl;
	}
	//3、遍历方式3 for_each
	for_each(v.begin(), v.end(), myPrint);
}

void test02() {
	//创建了一个vector容器
	vector<Person*> v;
	//插入数据
	Person p1("aa", 10);
	Person p2("aa", 20);
	Person p3("aa", 30);
	Person p4("aa", 40);
	Person p5("aa", 50);

	v.push_back(&p1);
	v.push_back(&p2);
	v.push_back(&p3);
	v.push_back(&p4);
	v.push_back(&p5);
	for (vector<Person *>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it)->m_Name << endl;
		cout << (*it)->Age << endl;
	}
}

int main() {
	test02();
	system("pause");
	return 0;
}