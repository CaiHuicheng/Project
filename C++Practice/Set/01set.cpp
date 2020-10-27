#include<iostream>
#include<string>
using namespace std;
#include<set>
//打印Set容器
void printSet(set<int> &s) {
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
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

	//拷贝构造
	set<int> s2(s1);
	printSet(s2);

	//赋值
	set<int> s3;
	s3 = s2;
	printSet(s3);
}
//大小和交换
void test02() {
	set<int> s1;
	//插入数据的方式 只有insert
	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	s1.insert(40);

	//判断是否为空
	if (s1.empty()) {
		cout << "为空" << endl;
	}
	else
	{
		cout << "不为空" << endl;
		cout << "大小" << s1.size() << endl;
	}

	set<int> s2;
	s2.insert(1);
	s2.insert(3);
	s2.insert(2);
	s2.insert(4);
	s2.insert(4);

	s2.swap(s1);
	printSet(s1);
}
//插入和删除
void test03() {
	set<int> s1;
	//插入
	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	s1.insert(40);
	//遍历
	printSet(s1);
	//删除
	s1.erase(s1.begin());
	printSet(s1);
	//20 30 40
	//删除重载版
	s1.erase(30);
	printSet(s1);
	//20 40

	//清空
	s1.clear();
}
//查找和统计
void test04() {
	set<int> s1;
	//插入
	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	s1.insert(40);
	//查找 返回的是迭代器 pos
	set<int>::iterator pos = s1.find(30);
	if (pos!=s1.end())
	{
		cout << "找到了" << *pos << endl;
	}
	else {
		cout << "没找到" << endl;
	}

	//统计  set返回的结果要么是0要么是1
	int num = s1.count(20);
	cout << num << endl;
}
int main() {
	//test01();
	//test02();
	//test03();
	test04();
	system("pause");
	return 0;
}