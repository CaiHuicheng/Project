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
		//降序
		return v1 > v2;
	}
};
class Worker {
public:
	string m_Name;
	int m_Salary;
};

//创建员工函数
void createWorker(vector<Worker> &v) {
	string nameSeed = "ABCDEFGIJR";
	for (int i = 0; i < 10; i++)
	{
		Worker w;
		w.m_Name = "员工";
		w.m_Name += nameSeed[i];

		w.m_Salary = rand() % 10000 + 10000;

		v.push_back(w);
	}
}

//员工分组函数
void setGroup(vector<Worker> &v, multimap<int, Worker> & m) {
	for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
		//产生随机部门编号
		int deptId = rand() % 3;//0`2

		//将员工插入分组中
		//key部门编号 value具体员工
		m.insert(make_pair(deptId, *it));
	}
}
//分组显示员工
void showWorkByGroup(multimap<int, Worker> & m) {
	cout << "策划部门:" << endl;
	int index = 0;
	int count = m.count(CEHUA);
	multimap<int, Worker>::iterator pos = m.find(CEHUA);
	for ( ;pos != m.end() && index<count ; pos++,index++)
	{
		cout << "姓名：" << pos->second.m_Name << "\t工资:" << pos->second.m_Salary << endl;
	}

	cout << "美术部门:" << endl;
	index = 0;
	count = m.count(MEISHU);
	pos = m.find(MEISHU);
	for (; pos != m.end() && index < count; pos++, index++)
	{
		cout << "姓名：" << pos->second.m_Name << "\t工资:" << pos->second.m_Salary << endl;
	}

	cout << "研发部门:" << endl;
	index = 0;
	count = m.count(YANFA);
	pos = m.find(YANFA);
	for (; pos != m.end() && index < count; pos++, index++)
	{
		cout << "姓名：" << pos->second.m_Name << "\t工资:" << pos->second.m_Salary << endl;
	}
	
}
//
void test01() {
	srand((unsigned int)time(NULL));

	//1、创建员工
	vector<Worker> v;
	createWorker(v);
	/*//测试
	for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
		cout << (*it).m_Name << endl;
	}*/
	//2、员工分组
	multimap<int, Worker> m;
	setGroup(v,m);
	/*//测试
	for (multimap<int, Worker>::iterator it = m.begin(); it != m.end(); it++) {
		cout<<it->first << "姓名：" << it->second.m_Name << "\t工资:" << it->second.m_Salary << endl;
	}*/

	//3、分组显示员工
	showWorkByGroup(m);
}



int main() {
	test01();

	system("pause");
	return 0;
}