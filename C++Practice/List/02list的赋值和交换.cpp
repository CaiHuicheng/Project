#include<iostream>
using namespace std;
#include<string>
#include<list>
//List 构造函数

void printList(const list<int> &L) {
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	list<int> L1;
	//添加数据
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	L1.push_back(40);
	L1.push_back(50);

	printList(L1);

	list<int> L2;
	L2 = L1;
	printList(L2);

	list<int> L3;
	L3.assign(L2.begin(), L2.end());
	printList(L3);

	list<int> L4(4, 10);
	printList(L4);

	//交换
	L4.swap(L1);
	printList(L4);
}

int main() {

	test01();
	system("pause");
	return 0;
}