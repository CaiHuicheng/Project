#include<iostream>
using namespace std;
//new�ؼ��� ��������new�������� 
int * func() {
	//�ڶ���������������
	//new���ص��Ǹ��������͵�ָ��
	int * p = new int(10);
	return p;
}

//new�ؼ��� ��������new��������
void func2() {
	int * arr = new int[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << "\t" << endl;
	}
	//ɾ��������ݣ����飩ʱ���ϡ���
	delete[] arr;
}

int main() {
	int * p = func();
	cout << *p << endl;
	cout << *p << endl;
	cout << *p << endl;
	func2();
	//�����������ɳ���Ա�����٣�����Ա�����ͷ�
	//�����Ҫ�ͷŶ��������ݣ����ùؼ��� delete
	delete p;
	//cout << *p << endl; //�ڴ��Ѿ��ͷ��ˣ����ܽ��з��ʷ��򱨴�
	system("pause");
	return 0;
}