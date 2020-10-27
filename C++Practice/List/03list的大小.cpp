#include<iostream>
#include<string>
#include<list>
using namespace std;

//list ��С���� ��vector����

void printList(const list<int> &L) {//ֻ�������� iterator�����޸����� ��const_iterator
	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	list<int> L1;
	for (int i = 0; i < 10; i++)
	{
		L1.push_back(i);
	}
	printList(L1);
	//��С����

	//�ж��Ƿ�Ϊ��
	if (L1.empty()) {
		cout << "Ϊ��" << endl;
	}
	else {
		cout << "��Ϊ��" << endl;
		printList(L1);
	}
	//����ָ����С  ��vector����һ��
	L1.resize(15, 1);
	printList(L1);
	L1.resize(5);
	printList(L1);

}

int main() {

	test01();
	system("pause");

	return 0;
}