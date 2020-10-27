#include<iostream>
#include<string>
#include<deque>
using namespace std;

//deque 构造函数

void printDeque(const deque<int> &d) {//只读迭代器 iterator可以修改数据 用const_iterator
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	deque<int> d1;
	for (int i = 0; i < 10; i++)
	{
		d1.push_back(i);
	}
	printDeque(d1);
	//复制操作
	deque<int> d2(d1.begin(), d1.end());
	printDeque(d2);
	deque<int> d3(10, 100);
	printDeque(d3);
	deque<int> d4(d3);
	printDeque(d4);
	
}

int main() {

	test01();
	system("pause");

	return 0;
}