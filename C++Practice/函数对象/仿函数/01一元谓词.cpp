#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>

/*
	�º��� ����ֵ������bool�������� ��Ϊν��
	һԪν��
*/
class GreaterFive {
public:
	bool operator()(int val) {
		return val > 5;
	}
};

class MyCompare {
public:
	bool operator()(int val1, int val2) {
		return val1 > val2;
	}
};


void test01() {
	vector<int> v;

	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//���������� ��û�д���5����
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());//������������

	if (it==v.end())
	{
		cout << "������" << endl;
	}
	else {
		cout << *it << endl;
	}
}

void test02() {
	vector<int> v;

	for (int i = 5; i < 10; i++)
	{
		v.push_back(i);
	}
	for (int i = 0; i < 5; i++)
	{
		v.push_back(i);
	}
	sort(v.begin(), v.end());
	
	for (vector<int>::iterator it = v.begin();it!=v.end();it++ )
	{
		cout << *it << " ";
	}
	cout << endl;

	//ʹ�ú������� �ı��㷨����  ��Ϊ�������Ӵ�С
	sort(v.begin(), v.end(), MyCompare());

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}


int main() {
	//test01();
	test02();
	system("pause");
	return 0;
}