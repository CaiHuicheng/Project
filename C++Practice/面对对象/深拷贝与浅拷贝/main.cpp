#include<iostream>
#include<string>
using namespace std;

//�򵥵ĸ�ֵ����
//�ڶ�����������ռ䣬���п�������

class Person {
public:
	Person() {
		cout << "Ĭ��" << endl;
	}
	Person(int age,int h) {
		cout << "�в�" << endl;
		m_age = age;
		m_h = new int(h);

	}
	~Person() {
		if (m_h !=NULL)
		{
			delete m_h;
			m_h = NULL;
		}
		cout << "��" << endl;
	}
	Person(const Person &p) {
		cout << "��������" << endl;
		m_age = p.m_age;
		m_h = new int(*p.m_h);
	}
	int m_age;
	int *m_h;
};

int main() {
	Person p1(16,180);
	cout << p1.m_age<<"  " << *p1.m_h << endl;
	//��������Դ�ظ��ͷ� p1��ռ���ڴ滹ûɾ��p2ҲҪռ��
	/*Person p2(p1);*/

	//����ͨ���Լ�ʵ�ֿ������캯�� �����������
	Person p2(p1);

	cout << p2.m_age << "  " << *p2.m_h << endl;
	system("pause");
	return 0;
}
