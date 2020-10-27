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
	//利用成员函数重载 左移运算符
	//不会使用成员函数重载 因为实现cout在左侧
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