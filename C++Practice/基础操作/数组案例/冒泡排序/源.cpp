#include<iostream>
using namespace std;

int main() {

	int arr[10] = { 8,4,3,6,9,2,10,1,7,5 };

	//����ǰ
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << "	";
	}
	cout << endl;


	//�������
	//�ܹ���������Ϊ Ԫ�ظ���-1
	for (int i = 0; i < 10-1; i++)
	{
		for (int j = 0; j < 10-1-i; j++) {
			if (arr[j]>arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}

	}

	//������
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << "	";
	}
	cout << endl;

	system("pause");
	return 0;
}