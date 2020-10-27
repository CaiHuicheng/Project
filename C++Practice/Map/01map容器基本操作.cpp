#include<iostream>
#include<string>
using namespace std;
#include<map>
//��ӡMap����
void printMap(map<int,int> &m) {
	for (map<int,int>::iterator it = m.begin(); it != m.end(); it++) {
		cout << it->first << " " << it->second << " " << endl;
	}
	cout << endl;
}
//��ֵ�빹��
void test01() {

	map<int, int> m;
	//�������ݵķ�ʽ ֻ��insert
	m.insert(pair<int, int>(1,10));
	m.insert(pair<int, int>(2,30));
	m.insert(pair<int, int>(3,20));
	m.insert(pair<int, int>(4,40));
	m.insert(pair<int, int>(5,40));
	//����Ԫ�ز���ʱ�Զ����� �Ҳ��ܲ�����ͬ��ֵ
	printMap(m);
	//10 20 30 40

	//��������
	map<int, int> m2(m);
	printMap(m2);

	//��ֵ
	map<int, int> m3;
	m3 = m2;
	printMap(m3);
}
//��С�ͽ���
void test02() {
	map<int,int> m;
	//�������ݵķ�ʽ 
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 30));
	m.insert(pair<int, int>(3, 20));
	m.insert(pair<int, int>(4, 40));
	m.insert(pair<int, int>(5, 40));
	//�ж��Ƿ�Ϊ��
	if (m.empty()) {
		cout << "mapΪ��" << endl;
	}
	else {
		cout << "map��Ϊ��" << endl;
		cout << m.size() << endl;
	}
	//����

	map<int, int> m2;
	//�������ݵķ�ʽ 
	m2.insert(pair<int, int>(1, 1));
	m2.insert(pair<int, int>(2, 3));
	m2.insert(pair<int, int>(3, 2));
	m2.insert(pair<int, int>(4, 4));
	m2.insert(pair<int, int>(5, 4));

	cout << "����ǰ��" << endl;
	printMap(m);
	m.swap(m2);
	cout << "������" << endl;
	printMap(m);
}
//�����ɾ��
void test03() {
	map<int, int> m;
	//�������ݵķ�ʽ ��һ��insert  
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 30));
	m.insert(pair<int, int>(3, 20));
	m.insert(pair<int, int>(4, 40));
	m.insert(pair<int, int>(5, 40));

	//�ڶ���
	m.insert(make_pair(6, 33));

	//������
	m.insert(map<int, int>::value_type(7, 90));

	//������  ��Ҫ������������  ���Է������� key
	m[8] = 80;
	cout << m[4] << endl;
	printMap(m);

	//ɾ��
	m.erase(m.begin());
	printMap(m);

	m.erase(5);//����keyɾ��
	printMap(m);

	m.clear();
}
//���Һ�ͳ��
void test04() {
	map<int, int> m;

	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 30));
	m.insert(pair<int, int>(3, 20));
	m.insert(pair<int, int>(4, 40));
	m.insert(pair<int, int>(5, 40));


	//����
	map<int, int>::iterator pos = m.find(4);
	if (pos!=m.end())
	{
		cout << "key=" << (*pos).first << "\tvalue=" << (*pos).second;
	}
	else {
		cout << "������" << endl;
	}

	
	//ͳ��
	int num = m.count(3);
	cout << "num=" << num << endl;
}
int main() {
	//test01();
	//test02();
	//test03();
	test04();
	system("pause");
	return 0;
}