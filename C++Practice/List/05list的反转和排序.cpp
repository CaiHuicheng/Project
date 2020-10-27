#include<iostream>
#include<string>
#include<list>
using namespace std;

//list 反转和排序

bool myCopare(int v1, int v2) {
	return v1 > v2;
}

void printList(const list<int> &L) {//只读迭代器 iterator可以修改数据 用const_iterator
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	list<int> L1;
	//尾插
	L1.push_back(10);
	L1.push_back(20);
	//头插
	L1.push_front(12);
	L1.push_front(13);
	//13 12 10 20
	printList(L1);

	//反转
	L1.reverse();
	printList(L1);

	//排序   所有不支持随机访问迭代器的容器，不可以用标准算法
	//		 不支持随机访问迭代器的容器，内部会通过对应的算法
	L1.sort();
	printList(L1);

	//从大到小排序
	L1.sort(myCopare);
	printList(L1);
}


int main() {

	test01();
	system("pause");
	return 0;
}