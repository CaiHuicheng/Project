#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>


/*
	常用查找算法
	find
	find_if
	adjacent_find
	binary_search
	count
	count_if
*/

class GreaterFive {
public:
	bool operator()(int val) {
		return val > 5;
	}
};

class Transfrom {
public:
	int operator()(int v) {
		return v;
	}
};

class Person {
public:
	Person(string name, int age) {
		this->m_Name = name;
		this->m_Age = age;
	}
	string m_Name;
	int m_Age;
};

class Greate20 {
public:
	bool operator()(const Person &p) {
		return p.m_Age > 30;
	}
};

//find
void test01() {
	//查找内置函数
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>::iterator it = find(v.begin(), v.end(), 5);
	if (it==v.end())
	{
		cout << "找不到" << endl;
	}
	else {
		cout << *it << endl;
	}
}
//find_if
void test02() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());
	if (it == v.end())
	{
		cout << "找不到" << endl;
	}
	else {
		cout << *it << endl;
	}
}
//adjacent_find
void test03() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	v.push_back(9);
	v.push_back(2);
	vector<int>::iterator pos = adjacent_find(v.begin(),v.end());
	if (pos == v.end())
	{
		cout << "未找到相同元素" << endl;
	}
	else {
		cout << "找到相同元素，第一个为" << *pos << endl;
	}
}
//binary_search 查找一个元素算法存在  返回bool  顺序查找
void test04() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//查找是否有5
	cout << binary_search(v.begin(), v.end(), 9) << endl;
}

//count
void test05() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i+3);
		v.push_back(i + 2);
		v.push_back(i + 3);
	}
	cout << count(v.begin(), v.end(), 9) << endl;
}
//count_if
void test06() {
	vector<Person> v;
	Person p1("刘备", 35);
	Person p2("关羽", 35);
	Person p3("张飞", 30);
	Person p4("曹操", 56);
	Person p5("赵云", 25);
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	//统计 大于30人数
	cout << count_if(v.begin(), v.end(), Greate20()) << endl;
}
int main() {
	test01();
	test02();
	test03();
	test04();
	test05();
	test06();
	system("pause");
	return 0;
}