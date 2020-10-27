#include<iostream>
using namespace std;

int main() {
	int arr[10] = { 1,2, 3, 4, 5, 6, 7, 8, 9, 10 };//定义数组初始化

	//打印逆置前数组
	cout << "打印逆置前数组：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i]<<"\t";
	}
	cout << endl;

	//数组逆置操作

	int buff;//存储逆置数
	int start = 0, end = 9;
	while (start<end)
	{
		buff = arr[end];
		arr[end] = arr[start];
		arr[start] = buff;
		start++;
		end--;
	}
	cout << "逆置后数组为：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout <<arr[i] << "\t";
	}
	cout << endl;
	system("pause");
	return 0;
}