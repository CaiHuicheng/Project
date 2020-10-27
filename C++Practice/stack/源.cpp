#include<iostream>
#include<stack>
#include<string>
using namespace std;

//栈 stack容器


void test01() {
	stack<int> s;

	//入栈
	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);

	//判断是否为空
	while (!s.empty())
	{
		cout << "栈顶元素为:"<< s.top() << endl;

		//出栈
		s.pop();
	}
	cout << "栈的大小：" << s.size() << endl;
}
int main() {
	test01();
	system("pause");
	return 0;
}