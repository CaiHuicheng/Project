#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//vectorr��������Զ�����������
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
	//������һ��vector����
	vector<Person> v;
	//��������
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
	//ͨ������������
	vector<Person>::iterator itbegin = v.begin();//��ʼ������ ָ�������е�һ��Ԫ��
	vector<Person>::iterator itend = v.end();//���������� ָ�����������һ��Ԫ�ص���һ��

	//1��������ʽ1 while
	while (itbegin != itend)
	{
		cout << (*itbegin).m_Name << endl;
		cout << (*itbegin).Age << endl;
		itbegin++;
	}
	//2��������ʽ2 for
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it).m_Name << endl;
		cout << (*it).Age << endl;
	}
	//3��������ʽ3 for_each
	for_each(v.begin(), v.end(), myPrint);
}

void test02() {
	//������һ��vector����
	vector<Person*> v;
	//��������
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