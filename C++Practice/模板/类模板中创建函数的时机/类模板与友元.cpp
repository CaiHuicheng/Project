#include<iostream>
#include<string>
using namespace std;

//ͨ��ȫ�ֺ��� ��ӡPerson��Ϣ
//��Ա����������ʵ��
template<class T1, class T2>
//��ǰ�ñ�����֪��Person����
class Person;
template<class T1, class T2>
void showPerson2(Person<T1, T2> p)
{
	cout << p.m_Name << p.m_age << endl;
}
template<class T1, class T2>
class Person
{
	//ȫ�ֺ��� ����ʵ��
	friend void showPerson1(Person<T1, T2> p)
	{
		cout << p.m_Name << p.m_age << endl;
	}
	//ȫ�ֺ��� ����ʵ��
	//�ӿ�ģ������б�
	//���ȫ�ֺ��� ��ǰ֪��
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