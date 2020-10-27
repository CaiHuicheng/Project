#include<iostream>
using namespace std;

void swap(int a, int b) {

	int temp = a;
	a = b;
	b = temp;
	cout << "a1=" << a << endl;
	cout << "b1=" << b << endl;
}

void swap002(int * p1, int * p2) {
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
	cout << "a1=" << *p1 << endl;
	cout << "b1=" << *p2 << endl;
}

int main() {

	//1、值传递

	int a = 10;
	int b = 20;

	/*swap(a, b);
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;*/
	swap002(&a, &b);

	//2、地址传递
	system("pause");
	return 0;
}