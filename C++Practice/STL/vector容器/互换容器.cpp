#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//vector ��������

//��������
void printVector(vector<int> &v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	vector<int> v;
	//�������� β�巨
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	
	printVector(v);

	vector<int> v2;
	for (int i = 10; i >0; i--)
	{
		v2.push_back(i);
	}
	printVector(v2);

	//������
	v.swap(v2);
	printVector(v);
	printVector(v2);
}

//ʵ������ ����swaps�����ռ�
void test02() {
	vector<int> v3;
	for (int i = 0; i < 10000; i++)
	{
		v3.push_back(i);
	}
	cout << "v3����:" << v3.capacity() << endl;
	cout << "v3��С��" << v3.size() << endl;
	//�޸Ĺ��� �����˷�
	v3.resize(3);
	cout << "v3����:" << v3.capacity() << endl;
	cout << "v3��С��" << v3.size() << endl;
	//����swapѹ������
	vector<int>(v3).swap(v3);
	cout << "v3����:" << v3.capacity() << endl;
	cout << "v3��С��" << v3.size() << endl;
}

int main() {

	test01();
	test02();
	system("pause");
	return 0;
}