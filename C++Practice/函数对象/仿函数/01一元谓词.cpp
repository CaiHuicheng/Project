#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>

/*
	仿函数 返回值类型是bool数据类型 称为谓词
	一元谓词
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
	//查找容器中 有没有大于5的数
	vector<int>::iterator it = find_if(v.begin(), v.end(), GreaterFive());//创建匿名对象

	if (it==v.end())
	{
		cout << "不存在" << endl;
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

	//使用函数对象 改变算法策略  变为排序规则从大到小
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