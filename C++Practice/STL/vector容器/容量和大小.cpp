#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//vector �����ʹ�С

void printVector(vector<int> &v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	vector<int> v;
	//��������
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	
	if (v.empty())
	{
		cout << "Ϊ��" << endl;
	}
	else {
		cout << "������" << v.capacity() << endl;
		cout << "��С:" << v.size() << endl;
	}

	//����ָ����С
	v.resize(15, 100);//����ָ����ԭ�ȳ���100Ϊʣ���Ĭ�����ֵ
	printVector(v);
	v.resize(4);//����ָ����ԭ�ȶ̣���ȥ
	printVector(v);
}

int main() {

	test01();
	system("pause");
	return 0;
}