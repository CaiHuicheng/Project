#include<iostream>
#include<string>
using namespace std;
#include<map>
#include<vector>
#include<ctime>

#define CEHUA 0
#define MEISHU 1
#define YANFA 2

class MyCompare {
public:
	bool operator()(int v1, int v2) {
		//����
		return v1 > v2;
	}
};
class Worker {
public:
	string m_Name;
	int m_Salary;
};

//����Ա������
void createWorker(vector<Worker> &v) {
	string nameSeed = "ABCDEFGIJR";
	for (int i = 0; i < 10; i++)
	{
		Worker w;
		w.m_Name = "Ա��";
		w.m_Name += nameSeed[i];

		w.m_Salary = rand() % 10000 + 10000;

		v.push_back(w);
	}
}

//Ա�����麯��
void setGroup(vector<Worker> &v, multimap<int, Worker> & m) {
	for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
		//����������ű��
		int deptId = rand() % 3;//0`2

		//��Ա�����������
		//key���ű�� value����Ա��
		m.insert(make_pair(deptId, *it));
	}
}
//������ʾԱ��
void showWorkByGroup(multimap<int, Worker> & m) {
	cout << "�߻�����:" << endl;
	int index = 0;
	int count = m.count(CEHUA);
	multimap<int, Worker>::iterator pos = m.find(CEHUA);
	for ( ;pos != m.end() && index<count ; pos++,index++)
	{
		cout << "������" << pos->second.m_Name << "\t����:" << pos->second.m_Salary << endl;
	}

	cout << "��������:" << endl;
	index = 0;
	count = m.count(MEISHU);
	pos = m.find(MEISHU);
	for (; pos != m.end() && index < count; pos++, index++)
	{
		cout << "������" << pos->second.m_Name << "\t����:" << pos->second.m_Salary << endl;
	}

	cout << "�з�����:" << endl;
	index = 0;
	count = m.count(YANFA);
	pos = m.find(YANFA);
	for (; pos != m.end() && index < count; pos++, index++)
	{
		cout << "������" << pos->second.m_Name << "\t����:" << pos->second.m_Salary << endl;
	}
	
}
//
void test01() {
	srand((unsigned int)time(NULL));

	//1������Ա��
	vector<Worker> v;
	createWorker(v);
	/*//����
	for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
		cout << (*it).m_Name << endl;
	}*/
	//2��Ա������
	multimap<int, Worker> m;
	setGroup(v,m);
	/*//����
	for (multimap<int, Worker>::iterator it = m.begin(); it != m.end(); it++) {
		cout<<it->first << "������" << it->second.m_Name << "\t����:" << it->second.m_Salary << endl;
	}*/

	//3��������ʾԱ��
	showWorkByGroup(m);
}



int main() {
	test01();

	system("pause");
	return 0;
}