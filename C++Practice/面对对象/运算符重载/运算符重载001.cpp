#include<iostream>
#include<string>
using namespace std;

//重载加法
//1、成员函数重载
//2、全局函数重载

class Person {
public:
	/*Person operator+(Person &p) {
		Person temp;
		temp.m_A = this->m_A + p.m_A;
		temp.m_B = this->m_B + p.m_B;
		return temp;
	}*/
	int m_A;
	int m_B;
};
Person operator+(Person &p1,Person &p2) {
	Person temp;
	temp.m_A = p1.m_A + p2.m_A;
	temp.m_B = p1.m_B + p2.m_B;
	return temp;
}
Person operator+(Person &p1,int num) {
	Person temp;
	temp.m_A = p1.m_A + num;
	temp.m_B = p1.m_B + num;
	return temp;
}

void test01() {
	Person p1;
	p1.m_A = 10;
	p1.m_B = 10;

	Person p2;
	p2.m_A = 10;
	p2.m_B = 10;
	//
	Person p3 = p1+p2;
	//方法重载
	Person p4 = p2 + 100;
	cout << "p3.m_A=" << p3.m_A << endl;
	cout << "p4.m_A=" << p4.m_A << endl;
}
int main() {

	test01();
	system("pause");
	return 0;
}