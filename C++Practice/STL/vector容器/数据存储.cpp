#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//vector 数据存储

//遍历函数
void printVector(vector<int> &v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	vector<int> v;
	//插入数据 尾插法
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	
	//通过[]访问
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	//通过at访问
	for (int i = 0; i < v.size(); i++)
	{
		cout << v.at(i) << " ";
	}
	cout << endl;

	//获取第一个元素
	cout << "第一个元素:" << v.front() << endl;

	//获取最后一个元素
	cout << "最后一个元素:" << v.back() << endl;
}

int main() {

	test01();
	system("pause");
	return 0;
}