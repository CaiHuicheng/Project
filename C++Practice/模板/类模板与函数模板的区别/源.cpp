#include<iostream>
#include<string>
using namespace std;
//��ģ���뺯��ģ�������
//1����ģ��û���Զ������Ƶ���ʹ�÷�ʽ
//2����ģ����ģ������б��п�����Ĭ�ϲ���

template <class NameType, class AgeType = int>//class AgeType = int ģ������б��п�����Ĭ�ϲ���
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
//1����ģ��û���Զ������Ƶ���ʹ�÷�ʽ
void test01() {
	//Person p1("���޿�", 999); //�޷����Զ��Ƶ�
	Person<string, int> p1("���޿�", 999);
	p1.showPerson();

}
//2����ģ����ģ������б��п�����Ĭ�ϲ���
void test02() {
	Person<string> p2("��˽�", 333);
	p2.showPerson();
}
int main() {

	test02();
	system("pause");
	return 0;
}