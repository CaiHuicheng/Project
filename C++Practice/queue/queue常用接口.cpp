#include<iostream>
#include<queue>
#include<string>
using namespace std;

//���� queue����


void test01() {
	queue<int> q;

	//���
	q.push(10);
	q.push(20);
	q.push(30);
	q.push(40);

	//�ж��Ƿ�Ϊ��
	while (!q.empty())
	{
		cout << "��ͷԪ��Ϊ:" << q.front() << endl;
		cout << "��βԪ��Ϊ:" << q.back() << endl;

		//��ջ
		q.pop();
	}
	cout << "ջ�Ĵ�С��" << q.size() << endl;
}
int main() {
	test01();
	system("pause");
	return 0;
}