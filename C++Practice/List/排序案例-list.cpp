#include<iostream>
#include<string>
#include<list>
using namespace std;

//list������


class Person {
public:
	Person(string name, int age,int height) {
		this->m_Name = name;
		this->Age = age;
		this->height = height;
	}
	string m_Name;
	int Age;
	int height;
};

bool comparePerson(Person &p1,Person &p2) {
	//������������ ����
	if (p1.Age==p2.Age)
	{
		//������ͬ �����������
		return p1.height > p2.height;
		
	}
	else {
		return p1.Age > p2.Age;
	}
	
}

void test01() {
	list<Person> L;//��������

	//¼������
	Person p1("����", 35, 175);
	Person p2("����", 30, 185);
	Person p3("�ŷ�", 29, 180);
	Person p4("����", 25, 187);
	Person p5("���", 35, 170);
	Person p6("��ܭ", 50, 165);

	//��������
	L.push_back(p1);
	L.push_back(p2);
	L.push_back(p3);
	L.push_back(p4);
	L.push_back(p5);
	L.push_back(p6);

	for (list<Person>::iterator it = L.begin(); it != L.end(); it++) {
		cout << "����:" << (*it).m_Name << "\t����:" << (*it).Age << "\t���:" << (*it).height << endl;

	}

	//����
	cout << "--------------------------------" << endl;
	cout << "�����:" << endl;
	L.sort(comparePerson);

	for (list<Person>::iterator it = L.begin(); it != L.end(); it++) {
		cout << "����:" << (*it).m_Name << "\t����:" << (*it).Age << "\t���:" << (*it).height << endl;

	}

}


int main() {

	test01();
	system("pause");
	return 0;
}