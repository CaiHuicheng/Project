#include<iostream>
#include<string>
using namespace std;
#include<set>

/*
	set 与 multiset 区别

	set不可以插入重复数据 multiset可以
	set插入数据的同时会返回插入的结果，表示插入成功
	multiset不会检测数据，因此可以插入重复数据
*/


//打印Set容器
void printSet(set<int> &s) {
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
//set 插入
void test01() {
	cout << "set 插入" << endl;
	set<int> s1;
	//接收s1插入的结果  pair<迭代器，bool>
	pair<set<int>::iterator,bool>ret = s1.insert(10);
	if (ret.second) {
		cout << "插入成功" << endl;
	}
	else
	{
		cout << "插入失败" << endl;
	}
	//第二次插入
	ret = s1.insert(10);
	if (ret.second) {
		cout << "插入成功" << endl;
	}
	else
	{
		cout << "插入失败" << endl;
	}
}
//multiset 插入
void test02() {
	cout << "multiset 插入" << endl;
	multiset<int> ms;
	//允许插入重复值
	ms.insert(10);
	ms.insert(10);
	for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++) {
		cout << *it << endl;
	}
	
}

int main() {
	test01();
	test02();
	system("pause");
	return 0;
}