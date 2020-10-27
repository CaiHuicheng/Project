#include<iostream>
#include<string>
using namespace std;
#include<set>
/*
对于自定义数据类型 都会指定排序规则
Set 利用仿函数 修改排序规则
*/

class Person {
public:
	Person(string name,int age) {
		this->m_Name = name;
		this->m_Age = age;
	}
	string m_Name;
	int m_Age;
};

//set容器排序
class MyCompare {
public:
	bool operator()(const Person& p1,const Person& p2) {
		//按照年龄排序 降序
		return p1.m_Age > p2.m_Age;
	}
};

//赋值与构造
void test01() {

	set<Person,MyCompare> s;
	//插入数据
	Person p1("刘备",30);
	Person p2("曹操", 38);
	Person p3("李云考虑", 33);
	Person p4("袁术", 50);
	Person p5("字串", 320);
	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);
	s.insert(p5);

	for (set<Person,MyCompare>::const_iterator it = s.begin(); it != s.end(); it++)
	{
		cout << (*it).m_Name<< (*it).m_Age<< " ";
	}
	cout << endl;

}

int main() {
	test01();
	system("pause");
	return 0;
}