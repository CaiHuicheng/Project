#include<iostream>
#include<stack>
#include<string>
using namespace std;

//ջ stack����


void test01() {
	stack<int> s;

	//��ջ
	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);

	//�ж��Ƿ�Ϊ��
	while (!s.empty())
	{
		cout << "ջ��Ԫ��Ϊ:"<< s.top() << endl;

		//��ջ
		s.pop();
	}
	cout << "ջ�Ĵ�С��" << s.size() << endl;
}
int main() {
	test01();
	system("pause");
	return 0;
}