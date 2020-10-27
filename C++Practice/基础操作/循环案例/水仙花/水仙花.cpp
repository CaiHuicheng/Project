#include<iostream>
using namespace std;
int main() {
	int num = 100, a, b, c;
	do
	{
		a = num % 10;
		b = num / 10 % 10;
		c = num / 100;
		if (a * a * a + b * b * b + c * c * c == num)
		{
			cout << "num = " << num << endl;
		}
		num++;

	} while (num<1000);
	system("pause");
	return 0;
}