#include<iostream>
using namespace std;

void swap(int num1, int num2) {
	cout << "交换前：" << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;

	int temp = num1;
	num1 = num2;
	num2 = temp;
	cout << "交换后：" << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;
}

int main() {
	int num1 = 10;
	int num2 = 20;
	swap(num1, num2);
	cout << "交换的过程中 实参的值：" << endl;
	cout << "num1 = " << num1 << endl;
	cout << "num2 = " << num2 << endl;
	system("pause");
	return 0;
}