#include<iostream>
using namespace std;

int main() {
	int arr[10] = { 1,2, 3, 4, 5, 6, 7, 8, 9, 10 };//���������ʼ��

	//��ӡ����ǰ����
	cout << "��ӡ����ǰ���飺" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i]<<"\t";
	}
	cout << endl;

	//�������ò���

	int buff;//�洢������
	int start = 0, end = 9;
	while (start<end)
	{
		buff = arr[end];
		arr[end] = arr[start];
		arr[start] = buff;
		start++;
		end--;
	}
	cout << "���ú�����Ϊ��" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout <<arr[i] << "\t";
	}
	cout << endl;
	system("pause");
	return 0;
}