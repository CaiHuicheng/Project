#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
//vector 插入和删除

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
	//遍历操作
	printVector(v);

	//尾删法
	v.pop_back();
	printVector(v);

	//插入 第一个参数是迭代器
	v.insert(v.begin(), 100);
	printVector(v);
	v.insert(v.begin(), 5, 6);
	printVector(v);

	//删除
	v.erase(v.end());
	printVector(v);

	v.clear();//v.erase(v.begin(),v.end());
	printVector(v);
	
}

int main() {

	test01();
	system("pause");
	return 0;
}