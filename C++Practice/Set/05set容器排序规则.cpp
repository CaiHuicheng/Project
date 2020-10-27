#include<iostream>
#include<string>
using namespace std;
#include<set>
/*
�����Զ����������� ����ָ���������
Set ���÷º��� �޸��������
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

//set��������
class MyCompare {
public:
	bool operator()(const Person& p1,const Person& p2) {
		//������������ ����
		return p1.m_Age > p2.m_Age;
	}
};

//��ֵ�빹��
void test01() {

	set<Person,MyCompare> s;
	//��������
	Person p1("����",30);
	Person p2("�ܲ�", 38);
	Person p3("���ƿ���", 33);
	Person p4("Ԭ��", 50);
	Person p5("�ִ�", 320);
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