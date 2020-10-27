#include<iostream>
using namespace std;
int main() {

	//三目运算符

	//变量a、b、c
	//将a和b做比较，将变量大的赋值给变量c
	int a = 10;
	int b = 5;
	int c = 15;
	c = (a > b ? a : b);
	cout << "c=" << c << endl;

	(a > b ? a : b) = 100;
	cout << "a=" << a << endl;
	system("pause");
	return 0;
}