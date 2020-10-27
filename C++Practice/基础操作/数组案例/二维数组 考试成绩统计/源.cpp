#include<iostream>
#include<string>
using namespace std;

int main() {

	//1、创建二维数组
	int scores[3][3] = {
		{100,100,90},
		{90,85,74},
		{60,59,50}
	};
	string names[3] = { "张三","李四","王五" };
	for (int i = 0;i < 3; i++)
	{
		int sum = 0;
		cout << names[i] << ":";
		for (int j = 0; j < 3; j++) {
			cout << scores[i][j] << " ";
			sum += scores[i][j];
		}
		cout << "sum=" << sum << endl;
	}

	system("pause");
	return 0;
}