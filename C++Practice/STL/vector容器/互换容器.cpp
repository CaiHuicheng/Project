#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//vector 容器互换

//遍历函数
void printVector(vector<int> &v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	vector<int> v;
	//插入数据 尾插法
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	
	printVector(v);

	vector<int> v2;
	for (int i = 10; i >0; i--)
	{
		v2.push_back(i);
	}
	printVector(v2);

	//交换后
	v.swap(v2);
	printVector(v);
	printVector(v2);
}

//实际作用 利用swaps收索空间
void test02() {
	vector<int> v3;
	for (int i = 0; i < 10000; i++)
	{
		v3.push_back(i);
	}
	cout << "v3容量:" << v3.capacity() << endl;
	cout << "v3大小：" << v3.size() << endl;
	//修改过后 容量浪费
	v3.resize(3);
	cout << "v3容量:" << v3.capacity() << endl;
	cout << "v3大小：" << v3.size() << endl;
	//利用swap压缩容量
	vector<int>(v3).swap(v3);
	cout << "v3容量:" << v3.capacity() << endl;
	cout << "v3大小：" << v3.size() << endl;
}

int main() {

	test01();
	test02();
	system("pause");
	return 0;
}