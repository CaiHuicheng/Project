#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//vector ���ݴ洢

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
	
	//ͨ��[]����
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	//ͨ��at����
	for (int i = 0; i < v.size(); i++)
	{
		cout << v.at(i) << " ";
	}
	cout << endl;

	//��ȡ��һ��Ԫ��
	cout << "��һ��Ԫ��:" << v.front() << endl;

	//��ȡ���һ��Ԫ��
	cout << "���һ��Ԫ��:" << v.back() << endl;
}

int main() {

	test01();
	system("pause");
	return 0;
}