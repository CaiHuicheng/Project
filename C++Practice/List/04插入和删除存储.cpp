#include<iostream>
#include<string>
#include<list>
using namespace std;

//list �����ɾ�� ��vector����

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

	//βɾ
	L1.pop_back();
	printList(L1);
	//13 12 10 
	//ͷɾ
	L1.pop_front();
	printList(L1);
	//12 10
	
	//insert����
	list<int>::iterator it = L1.begin();
	L1.insert(++it,1001);

	L1.insert(++it, 2, 1000);
	printList(L1);
	//12 1001 10 1000 1000

	//ɾ��
	it = L1.begin();
	L1.erase(++it);
	//12 10 1000 1000
	printList(L1);

	//�Ƴ� ɾ������ƥ��ֵ
	L1.push_back(10000);
	L1.push_back(10000);
	L1.push_back(10000);
	L1.push_back(10000);
	printList(L1);
	L1.remove(10000);
	printList(L1);

	//���
	L1.clear();
	printList(L1);

}

//���ݵĴ�ȡ
void test02() {
	list<int> L1;
	//β��
	L1.push_back(10);
	L1.push_back(20);
	//ͷ��
	L1.push_front(12);
	L1.push_front(13);
	//13 12 10 20
	printList(L1);

	//�������� [] �� at ����    ԭ��list���������� �洢�ռ䲻��������
	cout << "��һ��Ԫ��:" << L1.front() << endl;
	cout << "���һ��Ԫ��:" << L1.back() << endl;

}

int main() {

	//test01();
	test02();
	system("pause");

	return 0;
}