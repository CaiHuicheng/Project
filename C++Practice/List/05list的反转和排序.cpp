#include<iostream>
#include<string>
#include<list>
using namespace std;

//list ��ת������

bool myCopare(int v1, int v2) {
	return v1 > v2;
}

void printList(const list<int> &L) {//ֻ�������� iterator�����޸����� ��const_iterator
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	list<int> L1;
	//β��
	L1.push_back(10);
	L1.push_back(20);
	//ͷ��
	L1.push_front(12);
	L1.push_front(13);
	//13 12 10 20
	printList(L1);

	//��ת
	L1.reverse();
	printList(L1);

	//����   ���в�֧��������ʵ��������������������ñ�׼�㷨
	//		 ��֧��������ʵ��������������ڲ���ͨ����Ӧ���㷨
	L1.sort();
	printList(L1);

	//�Ӵ�С����
	L1.sort(myCopare);
	printList(L1);
}


int main() {

	test01();
	system("pause");
	return 0;
}