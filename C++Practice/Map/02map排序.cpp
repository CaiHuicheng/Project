#include<iostream>
#include<string>
using namespace std;
#include<map>

class MyCompare {
public:
	bool operator()(int v1, int v2) {
		//����
		return v1 > v2;
	}
};

//��ӡMap����
void printMap(map<int, int,MyCompare> &m) {
	for (map<int, int,MyCompare>::iterator it = m.begin(); it != m.end(); it++) {
		cout << it->first << " " << it->second << " " << endl;
	}
	cout << endl;
}
//��ֵ�빹��
void test01() {

	map<int, int,MyCompare> m;
	//�������ݵķ�ʽ ֻ��insert
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 30));
	m.insert(pair<int, int>(3, 20));
	m.insert(pair<int, int>(4, 40));
	m.insert(pair<int, int>(5, 40));
	printMap(m);
	
}



int main() {
	test01();
	
	system("pause");
	return 0;
}