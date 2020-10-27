#include<iostream>
using namespace std;

int main() {
	int arr[5];
	cout << "输入五只小猪体重" << endl;
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

	cout << "最重的小猪为：" << max<<"kg"<< endl;
	system("pause");

}