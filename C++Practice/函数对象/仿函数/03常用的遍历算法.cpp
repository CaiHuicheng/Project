#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<algorithm>


/*
	常用遍历算法
	for_each
	transform
*/

void print01(int val) {
	cout << val << " ";
}
class print02 {
public:
	void operator()(int val) {
		cout << val << " ";
	}
};

class Transfrom {
public:
	int operator()(int v) {
		return v;
	}
};

//for_each
void test01() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}

	for_each(v.begin(), v.end(), print01);
	cout << endl;
	for_each(v.begin(), v.end(), print02());
	cout << endl;
}
//transform
void test02() {
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int> vTarget;
	vTarget.resize(v.size());
	transform(v.begin(), v.end(), vTarget.begin(), Transfrom());
	for_each(v.begin(), v.end(), print02());

}


int main() {
	test01();
	test02();
	//test03();
	system("pause");
	return 0;
}