#include<iostream>
using namespace std;

int main() {
	int arr[5];
	cout << "������ֻС������" << endl;
	for (int  i = 0; i < 5; i++)
	{
		cin >> arr[i];
	}

	int max = 0;

	for (int i = 0; i < 5; i++)
	{
		if (max < arr[i]) {
			max = arr[i];
		}

	}

	cout << "���ص�С��Ϊ��" << max<<"kg"<< endl;
	system("pause");

}