#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//vector 容量和大小

void printVector(vector<int> &v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void test01() {
	vector<int> v;
	//插入数据
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);
	
	if (v.empty())
	{
		cout << "为空" << endl;
	}
	else {
		cout << "容量：" << v.capacity() << endl;
		cout << "大小:" << v.size() << endl;
	}

	//重新指定大小
	v.resize(15, 100);//重新指定比原先长，100为剩余的默认填充值
	printVector(v);
	v.resize(4);//重新指定比原先短，舍去
	printVector(v);
}

int main() {

	test01();
	system("pause");
	return 0;
}