#include<iostream>
#include<string>
#include<vector>
using namespace std;

void printVector(vector<int>&v) {
	for (vector<int>::iterator it = v.begin(); it !=v.end(); it++)
	{
		cout << *it << endl;
	}
}

void test01() {
	vector<int> v1;//Ĭ�Ϲ��� �޲�

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
	}

	printVector(v1);

	//ͨ�����䷽ʽ���й���
	vector<int> v2(v1.begin(), v1.end());
	printVector(v2);

	//n��elem��ʽ����
	vector<int>v3(10, 100);
	printVector(v3);

	vector<int>v4(v3);
	printVector(v4);

}

int main() {
	test01();
	system("pause");
	return 0;
}
