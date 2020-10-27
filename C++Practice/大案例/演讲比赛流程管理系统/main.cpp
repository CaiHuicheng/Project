#include<iostream>
using namespace std;
#include"speechManager.h"
#include<map>
#include<string>
#include<ctime>

int main() {
	//创建管理类对象
	SpeechManager sm;

	//加随机种子
	srand((unsigned int)time(NULL));

	/*//测试选手是否创建
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << it->first<<it->second.m_Name<<it->second.m_Score << " ";
	}
	cout << endl;
	*/
	//用于存储用户选择
	int choice = 0;

	while (true) {
		//显示菜单
		sm.show_Menu();
		cout << "请输入您的选择：";
		cin >> choice;
		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看往届记录
			sm.loadRecord();
			sm.showRecord();
			break;
		case 3://清空比赛记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");//清屏
			break;
		}
	}

	system("pause");
	return 0;
}