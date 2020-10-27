#include<iostream>
#include<string>
#include<deque>
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

	//βɾ
	d1.pop_back();
	printDeque(d1);
	//13 12 10 
	//ͷɾ
	d1.pop_front();
	printDeque(d1);
	//12 10
}

void test02() {
	deque<int> d1;
	d1.push_back(10);
	d1.push_back(20);
	d1.push_back(30);
	d1.push_back(40);
	d1.push_back(50);
	d1.push_front(100);
	d1.push_front(100);
	d1.push_front(100);
	//100 100 100 10 20 30 40 50
	printDeque(d1);

	//insert����
	d1.insert(d1.begin(), 1001);

	d1.insert(d1.begin(), 2, 1000);
	printDeque(d1);
	//1000 1000 1001 100 100 100 10 20 30 40 50

	//�����������
	deque<int> d2;
	d1.push_back(10);
	d1.push_back(20);
	d1.push_back(30);
	d1.insert(d1.begin(), d2.begin(), d2.end());
	printDeque(d1);
	//1000 1000 1001 100 100 100 10 20 30 40 50 10 20 30

	//ɾ��
	deque<int>::iterator it = d1.begin();
	it++;
	d1.erase(it);
	printDeque(d1);
	//1000 1001 100 100 100 10 20 30 40 50 10 20 30
	//��������ɾ��
	d1.erase(d1.begin(), d1.end());//d1.clear();
	printDeque(d1);

}

int main() {

	//test01();
	test02();
	system("pause");

	return 0;
}