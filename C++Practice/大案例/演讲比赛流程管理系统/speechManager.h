#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include<map>
#include<deque>
#include"speaker.h"
#include<algorithm>
#include<numeric>
#include<fstream>

class SpeechManager {
public:

	//构造函数
	SpeechManager();

	//显示菜单
	void show_Menu();

	//退出系统
	void exitSystem();

	//析构函数
	~SpeechManager();

	//初始化
	void initSpeech();

	//创建选手
	void GreateSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示比赛的分数
	void showScore();
	//保存分数
	void saveRecord();
	//读取数据
	void loadRecord();
	//判断文件是否为空
	bool fileIsEmpty;
	//存放往届成绩容器
	map<int, vector<string>> m_Record;
	//查看往届成绩
	void showRecord();
	//清空记录
	void clearRecord();

	//比赛选手 容器 12人
	vector<int> v1;
	//第一轮晋级赛容器 6人
	vector<int> v2;
	//胜利的前三名 3 人
	vector<int> vVictory;
	//存放编程 以及对应的具体选手 容器
	map<int, Speaker> m_Speaker;
	//记录比赛轮数
	int m_Index;
};

