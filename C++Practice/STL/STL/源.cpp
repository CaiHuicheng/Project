#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//vectorr容器存放内置数据类型

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
	while (itBegin!=itEnd)
	{
		cout << *itBegin << endl;
		itBegin++;
	}
	//2、遍历方式2 for
	for (vector<int>::iterator it = v.begin(); it !=v.end(); it++)
	{
		cout << *it << endl;
	}
	//3、遍历方式3 for_each
	for_each(v.begin(), v.end(), myPrint);
}

int main() {
	test01();
	system("pause");
	return 0;
}