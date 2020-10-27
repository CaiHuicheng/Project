#include<iostream>
#include<string>
#include<list>
using namespace std;

//list 插入和删除 与vector类似

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

	//尾删
	L1.pop_back();
	printList(L1);
	//13 12 10 
	//头删
	L1.pop_front();
	printList(L1);
	//12 10
	
	//insert插入
	list<int>::iterator it = L1.begin();
	L1.insert(++it,1001);

	L1.insert(++it, 2, 1000);
	printList(L1);
	//12 1001 10 1000 1000

	//删除
	it = L1.begin();
	L1.erase(++it);
	//12 10 1000 1000
	printList(L1);

	//移除 删除所有匹配值
	L1.push_back(10000);
	L1.push_back(10000);
	L1.push_back(10000);
	L1.push_back(10000);
	printList(L1);
	L1.remove(10000);
	printList(L1);

	//清除
	L1.clear();
	printList(L1);

}

//数据的存取
void test02() {
	list<int> L1;
	//尾插
	L1.push_back(10);
	L1.push_back(20);
	//头插
	L1.push_front(12);
	L1.push_front(13);
	//13 12 10 20
	printList(L1);

	//不可以用 [] 和 at 访问    原因list本质是链表 存储空间不是连续的
	cout << "第一个元素:" << L1.front() << endl;
	cout << "最后一个元素:" << L1.back() << endl;

}

int main() {

	//test01();
	test02();
	system("pause");

	return 0;
}