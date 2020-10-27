#include<iostream>
#include<string>
#include<deque>
using namespace std;

//deque ��С���� ��vector����

void printDeque(const deque<int> &d) {//ֻ�������� iterator�����޸����� ��const_iterator
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
	//��С����
	
	//�ж��Ƿ�Ϊ��
	if (d1.empty()) {
		cout << "Ϊ��" << endl;
	}
	else {
		cout << "��Ϊ��" << endl;
		printDeque(d1);
	}
	//����ָ����С  ��vector����һ��
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