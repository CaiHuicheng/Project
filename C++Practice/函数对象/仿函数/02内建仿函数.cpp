#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>
#include<functional>
//�ڽ��º���ͷ�ļ�

/*
	�����º���  negate һԪ�º��� ȡ��    plus ��Ԫ�º��� �ӷ�
	��ϵ�º���
	�߼��º���
*/

class MyCompare {
public:
	bool operator()(int val1, int val2) {
		return val1 > val2;
	}
};
//�����º���
void test01() {
	//һԪ ȡ��
	negate<int> n;
	cout << n(50) << endl;

	//��Ԫ �Ӽ��˳�
	plus<int> p;
	minus<int> m;
	divides<int> d;
	multiplies<int> mul;
	modulus<int> mod;
	cout << p(30, 20) << endl;//��
	cout << m(100, 10) << endl;//��
	cout << d(99, 9) << endl;//��
	cout << mul(9, 9) << endl;//��
	cout << mod(59, 8) << endl;//ģ



}
//��ϵ�º���
void test02() {
	//����
	vector<int> v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(50);
	v.push_back(30);
	v.push_back(20);

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
	sort(v.begin(), v.end(),greater<int>());
	//sort(v.begin(), v.end(), MyCompare());
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}
//�߼��º���
void test03() {
	//�߼���
	vector<bool> v;
	v.push_back(true);
	v.push_back(true);
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);

	for (vector<bool>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	//�����߼��� ������v���˵� ����v2�� ��ִ��ȡ������
	vector<bool> v2;
	v2.resize(v.size());
	transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());
	for (vector<bool>::iterator it = v2.begin(); it != v2.end(); it++) {
		cout << *it << " ";
	}
}


int main() {
	//test01();
	//test02();
	test03();
	system("pause");
	return 0;
}