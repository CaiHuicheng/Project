#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>


/*
	���ò����㷨
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
	//�������ú���
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>::iterator it = find(v.begin(), v.end(), 5);
	if (it==v.end())
	{
		cout << "�Ҳ���" << endl;
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
		cout << "�Ҳ���" << endl;
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
		cout << "δ�ҵ���ͬԪ��" << endl;
	}
	else {
		cout << "�ҵ���ͬԪ�أ���һ��Ϊ" << *pos << endl;
	}
}
//binary_search ����һ��Ԫ���㷨����  ����bool  ˳�����
void test04() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//�����Ƿ���5
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
	Person p1("����", 35);
	Person p2("����", 35);
	Person p3("�ŷ�", 30);
	Person p4("�ܲ�", 56);
	Person p5("����", 25);
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	//ͳ�� ����30����
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