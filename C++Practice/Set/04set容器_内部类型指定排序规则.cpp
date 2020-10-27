#include<iostream>
#include<string>
using namespace std;
#include<set>
/*
Set 利用仿函数 修改排序规则
*/

//打印Set容器
void printSet(set<int> &s) {
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

//set容器排序
class MyCompare {
public:
	bool operator()(int v1, int v2) {
		return v1 > v2;
	}
};

//赋值与构造
void test01() {

	set<int> s1;
	//插入数据的方式 只有insert
	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	s1.insert(40);
	//所有元素插入时自动排序 且不能插入相同的值
	printSet(s1);
	//10 20 30 40

	//指定排序规则 从大到小

	set<int,MyCompare> s2;
	//插入数据的方式 只有insert
	s2.insert(10);
	s2.insert(30);
	s2.insert(20);
	s2.insert(40);
	s2.insert(40);

	for (set<int, MyCompare>::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

}

int main() {
	test01();
	system("pause");
	return 0;
}