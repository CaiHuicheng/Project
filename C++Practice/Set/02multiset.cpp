#include<iostream>
#include<string>
using namespace std;
#include<set>

/*
	set �� multiset ����

	set�����Բ����ظ����� multiset����
	set�������ݵ�ͬʱ�᷵�ز���Ľ������ʾ����ɹ�
	multiset���������ݣ���˿��Բ����ظ�����
*/


//��ӡSet����
void printSet(set<int> &s) {
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
//set ����
void test01() {
	cout << "set ����" << endl;
	set<int> s1;
	//����s1����Ľ��  pair<��������bool>
	pair<set<int>::iterator,bool>ret = s1.insert(10);
	if (ret.second) {
		cout << "����ɹ�" << endl;
	}
	else
	{
		cout << "����ʧ��" << endl;
	}
	//�ڶ��β���
	ret = s1.insert(10);
	if (ret.second) {
		cout << "����ɹ�" << endl;
	}
	else
	{
		cout << "����ʧ��" << endl;
	}
}
//multiset ����
void test02() {
	cout << "multiset ����" << endl;
	multiset<int> ms;
	//��������ظ�ֵ
	ms.insert(10);
	ms.insert(10);
	for (multiset<int>::iterator it = ms.begin(); it != ms.end(); it++) {
		cout << *it << endl;
	}
	
}

int main() {
	test01();
	test02();
	system("pause");
	return 0;
}