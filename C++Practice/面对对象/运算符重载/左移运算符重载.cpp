#include<iostream>
#include<string>
using namespace std;

class Person {
	friend ostream & operator<<(ostream &cout, Person &p);
public:
	Person(int a, int b) {
		this->a = a;
		this->b = b;
	}
private:
	//���ó�Ա�������� ���������
	//����ʹ�ó�Ա�������� ��Ϊʵ��cout�����
	/*void operator<<(cout) {

	}*/
	int a;
	int b;
};
ostream & operator<<(ostream &cout,Person &p) {
	cout << "A=" << p.a << " B=" << p.b;
	return cout;
}

void test01() {
	Person p(10,10);
	cout << p << endl;
}
int main() {
	test01();
	system("pause");
	return 0;
}