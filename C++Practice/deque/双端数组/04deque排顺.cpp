#include<iostream>
#include<string>
#include<deque>
#include<algorithm>//�㷨�ı�׼��
using namespace std;

//deque ������ɾ��

void printDeque(const deque<int> &d) {//ֻ�������� iterator�����޸����� ��const_iterator
	for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	deque<int> d1;
	//β��
	d1.push_back(10);
	d1.push_back(20);
	//ͷ��
	d1.push_front(12);
	d1.push_front(13);
	//13 12 10 20
	printDeque(d1);

	//���� sort��׼��Ϊ�Ӵ�С
	sort(d1.begin(), d1.end());
	printDeque(d1);
}

int main() {

	test01();
	
	system("pause");

	return 0;
}