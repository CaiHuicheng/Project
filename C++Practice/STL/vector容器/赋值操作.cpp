#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//vectorr 赋值

void myPrint(int val) {
	cout << val << endl;
}
void test01() {
	//创建了一个vector容器
	vector<int> v;
	//插入数据
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	//通过迭代器访问
	vector<int>::iterator itBegin = v.begin();//起始迭代器 指向容器中第一个元素
	vector<int>::iterator itEnd = v.end();//结束迭代器 指向容器中最后一个元素的下一个

	//1、遍历方式1 while
	while (itBegin != itEnd)
	{
		cout << *itBegin << endl;
		itBegin++;
	}
	//2、遍历方式2 for
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
	//3、遍历方式3 for_each
	for_each(v.begin(), v.end(), myPrint);
}
//赋值操作
void printVector(vector<int> &v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << endl;
	}
}

void test02() {
	vector<int> v;
	//插入数据
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	//operator=赋值
	vector<int> v2;
	v2 = v;
	printVector(v2);
	//assgin赋值
	vector<int> v3;
	v3.assign(v2.begin(),v2.end());
	printVector(v3);

	vector<int> v4;
	v4.assign(10, 100);
}

int main() {

	test02();
	system("pause");
	return 0;
}