#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>
#include<functional>
//内建仿函数头文件

/*
	算数仿函数  negate 一元仿函数 取反    plus 二元仿函数 加法
	关系仿函数
	逻辑仿函数
*/

class MyCompare {
public:
	bool operator()(int val1, int val2) {
		return val1 > val2;
	}
};
//算数仿函数
void test01() {
	//一元 取反
	negate<int> n;
	cout << n(50) << endl;

	//二元 加减乘除
	plus<int> p;
	minus<int> m;
	divides<int> d;
	multiplies<int> mul;
	modulus<int> mod;
	cout << p(30, 20) << endl;//加
	cout << m(100, 10) << endl;//减
	cout << d(99, 9) << endl;//除
	cout << mul(9, 9) << endl;//乘
	cout << mod(59, 8) << endl;//模



}
//关系仿函数
void test02() {
	//大于
	vector<int> v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(50);
	v.push_back(30);
	v.push_back(20);

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
	sort(v.begin(), v.end(),greater<int>());
	//sort(v.begin(), v.end(), MyCompare());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
//逻辑仿函数
void test03() {
	//逻辑非
	vector<bool> v;
	v.push_back(true);
	v.push_back(true);
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);

	for (vector<bool>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	//利用逻辑非 将容器v搬运到 容器v2中 并执行取反操作
	vector<bool> v2;
	v2.resize(v.size());
	transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());
	for (vector<bool>::iterator it = v2.begin(); it != v2.end(); it++) {
		cout << *it << " ";
	}
}


int main() {
	//test01();
	//test02();
	test03();
	system("pause");
	return 0;
}