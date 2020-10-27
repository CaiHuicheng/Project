#include<iostream>
#include<string>
using namespace std;
#include<set>
//��ӡSet����
void printSet(set<int> &s) {
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
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

	//��������
	set<int> s2(s1);
	printSet(s2);

	//��ֵ
	set<int> s3;
	s3 = s2;
	printSet(s3);
}
//��С�ͽ���
void test02() {
	set<int> s1;
	//�������ݵķ�ʽ ֻ��insert
	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	s1.insert(40);

	//�ж��Ƿ�Ϊ��
	if (s1.empty()) {
		cout << "Ϊ��" << endl;
	}
	else
	{
		cout << "��Ϊ��" << endl;
		cout << "��С" << s1.size() << endl;
	}

	set<int> s2;
	s2.insert(1);
	s2.insert(3);
	s2.insert(2);
	s2.insert(4);
	s2.insert(4);

	s2.swap(s1);
	printSet(s1);
}
//�����ɾ��
void test03() {
	set<int> s1;
	//����
	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	s1.insert(40);
	//����
	printSet(s1);
	//ɾ��
	s1.erase(s1.begin());
	printSet(s1);
	//20 30 40
	//ɾ�����ذ�
	s1.erase(30);
	printSet(s1);
	//20 40

	//���
	s1.clear();
}
//���Һ�ͳ��
void test04() {
	set<int> s1;
	//����
	s1.insert(10);
	s1.insert(30);
	s1.insert(20);
	s1.insert(40);
	s1.insert(40);
	//���� ���ص��ǵ����� pos
	set<int>::iterator pos = s1.find(30);
	if (pos!=s1.end())
	{
		cout << "�ҵ���" << *pos << endl;
	}
	else {
		cout << "û�ҵ�" << endl;
	}

	//ͳ��  set���صĽ��Ҫô��0Ҫô��1
	int num = s1.count(20);
	cout << num << endl;
}
int main() {
	//test01();
	//test02();
	//test03();
	test04();
	system("pause");
	return 0;
}