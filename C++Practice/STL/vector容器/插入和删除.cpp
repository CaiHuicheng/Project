#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//vector �����ɾ��

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
	//��������
	printVector(v);

	//βɾ��
	v.pop_back();
	printVector(v);

	//���� ��һ�������ǵ�����
	v.insert(v.begin(), 100);
	printVector(v);
	v.insert(v.begin(), 5, 6);
	printVector(v);

	//ɾ��
	v.erase(v.end());
	printVector(v);

	v.clear();//v.erase(v.begin(),v.end());
	printVector(v);
	
}

int main() {

	test01();
	system("pause");
	return 0;
}