#include<iostream>
#include<string>
using namespace std;
#include<map>
//打印Map容器
void printMap(map<int,int> &m) {
	for (map<int,int>::iterator it = m.begin(); it != m.end(); it++) {
		cout << it->first << " " << it->second << " " << endl;
	}
	cout << endl;
}
//赋值与构造
void test01() {

	map<int, int> m;
	//插入数据的方式 只有insert
	m.insert(pair<int, int>(1,10));
	m.insert(pair<int, int>(2,30));
	m.insert(pair<int, int>(3,20));
	m.insert(pair<int, int>(4,40));
	m.insert(pair<int, int>(5,40));
	//所有元素插入时自动排序 且不能插入相同的值
	printMap(m);
	//10 20 30 40

	//拷贝构造
	map<int, int> m2(m);
	printMap(m2);

	//赋值
	map<int, int> m3;
	m3 = m2;
	printMap(m3);
}
//大小和交换
void test02() {
	map<int,int> m;
	//插入数据的方式 
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 30));
	m.insert(pair<int, int>(3, 20));
	m.insert(pair<int, int>(4, 40));
	m.insert(pair<int, int>(5, 40));
	//判断是否为空
	if (m.empty()) {
		cout << "map为空" << endl;
	}
	else {
		cout << "map不为空" << endl;
		cout << m.size() << endl;
	}
	//交换

	map<int, int> m2;
	//插入数据的方式 
	m2.insert(pair<int, int>(1, 1));
	m2.insert(pair<int, int>(2, 3));
	m2.insert(pair<int, int>(3, 2));
	m2.insert(pair<int, int>(4, 4));
	m2.insert(pair<int, int>(5, 4));

	cout << "交换前；" << endl;
	printMap(m);
	m.swap(m2);
	cout << "交换后；" << endl;
	printMap(m);
}
//插入和删除
void test03() {
	map<int, int> m;
	//插入数据的方式 第一种insert  
	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 30));
	m.insert(pair<int, int>(3, 20));
	m.insert(pair<int, int>(4, 40));
	m.insert(pair<int, int>(5, 40));

	//第二种
	m.insert(make_pair(6, 33));

	//第三中
	m.insert(map<int, int>::value_type(7, 90));

	//第四种  不要用来插入数据  可以访问数据 key
	m[8] = 80;
	cout << m[4] << endl;
	printMap(m);

	//删除
	m.erase(m.begin());
	printMap(m);

	m.erase(5);//按照key删除
	printMap(m);

	m.clear();
}
//查找和统计
void test04() {
	map<int, int> m;

	m.insert(pair<int, int>(1, 10));
	m.insert(pair<int, int>(2, 30));
	m.insert(pair<int, int>(3, 20));
	m.insert(pair<int, int>(4, 40));
	m.insert(pair<int, int>(5, 40));


	//查找
	map<int, int>::iterator pos = m.find(4);
	if (pos!=m.end())
	{
		cout << "key=" << (*pos).first << "\tvalue=" << (*pos).second;
	}
	else {
		cout << "不存在" << endl;
	}

	
	//统计
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