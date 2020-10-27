#include<iostream>
#include<string>
#include<list>
using namespace std;

//list 大小操作 与vector类似

void printList(const list<int> &L) {//只读迭代器 iterator可以修改数据 用const_iterator
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	list<int> L1;
	for (int i = 0; i < 10; i++)
	{
		L1.push_back(i);
	}
	printList(L1);
	//大小操作

	//判断是否为空
	if (L1.empty()) {
		cout << "为空" << endl;
	}
	else {
		cout << "不为空" << endl;
		printList(L1);
	}
	//重新指定大小  与vector规则一致
	L1.resize(15, 1);
	printList(L1);
	L1.resize(5);
	printList(L1);

}

int main() {

	test01();
	system("pause");

	return 0;
}