#include<iostream>
using namespace std;
int add(int, int);
int main() {
	int a = 10, b = 4;
	int num = add(a, b);
	cout << a << "+" << b << "=" << num << endl;
	system("pause");
	return 0;
}

int add(int num1, int num2) {
	return num1 + num2;
}