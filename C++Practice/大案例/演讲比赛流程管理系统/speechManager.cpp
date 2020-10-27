#include"speechManager.h"

//构造函数
SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->GreateSpeaker();
}

//显示函数
void SpeechManager::show_Menu() {
	cout << "***************************************" << endl;
	cout << "*********演讲比赛流程管理系统**********" << endl;
	cout << "*********1、开始演讲比赛     **********" << endl;
	cout << "*********2、查看往届记录     **********" << endl;
	cout << "*********3、清空比赛记录     **********" << endl;
	cout << "*********0、退出比赛系统     *********" << endl;
	cout << "***************************************" << endl;
}
//退出函数
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
//创建选手容器
void SpeechManager::initSpeech() {
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;
	//将记录的容器也清空
	this->m_Record.clear();
}

//开始比赛
void SpeechManager::startSpeech() {
	//第一轮比赛
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示信息
	this->showScore();
	//第二轮比赛
	this->m_Index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechContest();
	//3、显示最终结果
	this->showScore();
	//4、保存分数
	this->saveRecord();

	//重置比赛，获取记录
	this->initSpeech();
	this->GreateSpeaker();
	this->loadRecord();

	cout << "本届比赛结束！！！" << endl;
	system("pause");
	system("cls");
}
//成绩抽签函数
void SpeechManager::speechDraw() {
	cout << "第《" << this->m_Index << "》" << "轮比赛选手正在抽签" << endl;
	cout << "抽签后演讲顺序如下:" << endl;
	if (this->m_Index == 1) {
		//第一轮
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << "\t";
		}
		cout << endl;
	}
	else {
		//第二轮
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << "\t";
		}
		cout << endl;
	}
}

//创建选手
void SpeechManager::GreateSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];
		//创建具体选手
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2 ; j++)
		{
			sp.m_Score[j] = 0;
		}

		//创建选手编号
		this->v1.push_back(i + 10001);

		//选手编号以及对应选手信息 放到map中
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

//比赛
void SpeechManager::speechContest() {
	cout << "----------------------第" << this->m_Index << "轮比赛开始：------------------------------" << endl;

	multimap<double, int, greater<double>> groupScore;//临时容器 保存key分数 和value选手编号

	int num = 0;//记录人员数 6 人为一组
	vector<int> v_Src;//比赛的人员容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	//遍历所有参赛人员
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;

		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;//600~1000
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//排序
		d.pop_front();//去最高分
		d.pop_back();//去最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);//获取总分
		double avg = sum / (double)d.size();//获取平均分

		//每个人平均分
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6人一组 用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "\t姓名：" << this->m_Speaker[it->second].m_Name << "/t成绩：" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//取前三名
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}

	}

	cout << "----------------------第" << this->m_Index << "轮比赛结束！------------------------------" << endl;
	
	system("pause");
}

//显示分数
void SpeechManager::showScore() {
	cout << "----------------------第" << this->m_Index << "轮晋级选手如下：----------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "编号：" << *it << "\t姓名：" <<m_Speaker[*it].m_Name << "/t成绩：" <<m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
//保存数据
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//用输出的方式打开文件  --写文件
	//将每个人的信息写入文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	//关闭文件
	ofs.close();
	cout << "文件已经保存" << endl;
	//更改文件状态
	this->fileIsEmpty = false;
}
//读取数据
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);//输入流对象 读取文件
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//将上面读取的单个字符 放回来
	string data;
	int index = 0;
	while (ifs >> data) {
		//cout << data << endl;
		vector<string> v;//存放6个字符串信息 前三名数据
		int pos = -1;//查到逗号的位置
		int start = 0;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//没有找到
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件为空和不存在!" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "届" <<
			"冠军编号：" << this->m_Record[i][0] << "\t得分：" << this->m_Record[i][1] <<
			"亚军编号：" << this->m_Record[i][2] << "\t得分：" << this->m_Record[i][3] <<
			"季军编号：" << this->m_Record[i][4] << "\t得分：" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、取消" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在输出文件重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化属性
		this->initSpeech();
		//创建选手
		this->GreateSpeaker();
		//获取往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

//析构函数
SpeechManager::~SpeechManager() {

}