#include<iostream>
#include<string>
#include<deque>
using namespace std;

//deque 大小操作 与vector类似

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
	//大小操作
	
	//判断是否为空
	if (d1.empty()) {
		cout << "为空" << endl;
	}
	else {
		cout << "不为空" << endl;
		printDeque(d1);
	}
	//重新指定大小  与vector规则一致
	d1.resize(15, 1);
	printDeque(d1);
	d1.resize(5);
	printDeque(d1);

}

int main() {

	test01();
	system("pause");

	return 0;
}