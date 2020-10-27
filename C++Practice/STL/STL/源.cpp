#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//vectorr�������������������

void myPrint(int val) {
	cout << val << endl;
}
void test01() {
	//������һ��vector����
	vector<int> v;
	//��������
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	//ͨ������������
	vector<int>::iterator itBegin = v.begin();//��ʼ������ ָ�������е�һ��Ԫ��
	vector<int>::iterator itEnd = v.end();//���������� ָ�����������һ��Ԫ�ص���һ��

	//1��������ʽ1 while
	while (itBegin!=itEnd)
	{
		cout << *itBegin << endl;
		itBegin++;
	}
	//2��������ʽ2 for
	for (vector<int>::iterator it = v.begin(); it !=v.end(); it++)
	{
		cout << *it << endl;
	}
	//3��������ʽ3 for_each
	for_each(v.begin(), v.end(), myPrint);
}

int main() {
	test01();
	system("pause");
	return 0;
}