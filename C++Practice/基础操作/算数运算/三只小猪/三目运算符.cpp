#include<iostream>
using namespace std;
int main() {

	//��Ŀ�����

	//����a��b��c
	//��a��b���Ƚϣ���������ĸ�ֵ������c
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