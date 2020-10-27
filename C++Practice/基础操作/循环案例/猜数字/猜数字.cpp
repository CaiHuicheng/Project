#include<iostream>
#include<ctime>
using namespace std;
int main() {
	//1、系统生成随机数 注意添加时间种子
	srand((unsigned int)time(NULL));
	int num = rand() % 100 + 1;//1~100的值
	//2、玩家进行猜测
	int val = 0;
	
	//3、判断玩家的猜测
	while (1)
	{
		cin >> val;
		if (val > num)
		{
			cout << "猜测过大" << endl;
		}
		else if (val < num)
		{
			cout << "猜测过小" << endl;
		}
		else
		{
			cout << "恭喜猜对了" << endl;
			break;
		}
	}
	return 0;
}