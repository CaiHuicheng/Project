#include<iostream>
#include<queue>
#include<string>
using namespace std;

//队列 queue容器


void test01() {
	queue<int> q;

	//入对
	q.push(10);
	q.push(20);
	q.push(30);
	q.push(40);

	//判断是否为空
	while (!q.empty())
	{
		cout << "队头元素为:" << q.front() << endl;
		cout << "队尾元素为:" << q.back() << endl;

		//出栈
		q.pop();
	}
	cout << "栈的大小：" << q.size() << endl;
}
int main() {
	test01();
	system("pause");
	return 0;
}