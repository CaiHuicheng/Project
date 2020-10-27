#include<iostream>
#include<string>
#include<deque>
#include<algorithm>//算法的标准库
using namespace std;

//deque 插入与删除

void printDeque(const deque<int> &d) {//只读迭代器 iterator可以修改数据 用const_iterator
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	deque<int> d1;
	//尾插
	d1.push_back(10);
	d1.push_back(20);
	//头插
	d1.push_front(12);
	d1.push_front(13);
	//13 12 10 20
	printDeque(d1);

	//排序 sort标准库为从大到小
	sort(d1.begin(), d1.end());
	printDeque(d1);
}

int main() {

	test01();
	
	system("pause");

	return 0;
}