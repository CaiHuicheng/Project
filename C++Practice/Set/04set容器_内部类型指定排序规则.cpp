#include<iostream>
#include<string>
using namespace std;
#include<set>
/*
Set ���÷º��� �޸��������
*/

//��ӡSet����
void printSet(set<int> &s) {
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

//set��������
class MyCompare {
public:
	bool operator()(int v1, int v2) {
		return v1 > v2;
	}
};

//��ֵ�빹��
void test01() {

	set<int> s1;
	//�������ݵķ�ʽ ֻ��insert
	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	s1.insert(40);
	//����Ԫ�ز���ʱ�Զ����� �Ҳ��ܲ�����ͬ��ֵ
	printSet(s1);
	//10 20 30 40

	//ָ��������� �Ӵ�С

	set<int,MyCompare> s2;
	//�������ݵķ�ʽ ֻ��insert
	s2.insert(10);
	s2.insert(30);
	s2.insert(20);
	s2.insert(40);
	s2.insert(40);

	for (set<int, MyCompare>::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;

}

int main() {
	test01();
	system("pause");
	return 0;
}