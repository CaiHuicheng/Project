#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <deque>
#include <numeric>
#include <functional>

using namespace std;
class Student
{
public:
	string m_name;
	int m_scores[3];
};

//创建选手
void Init_Cadidate(map<int, Student>& map, vector<int>& v)
{
	string seed = "ABCDEFGHIJKLMNOPQISTUVWXYZ";
	for (int i = 0; i < 24; i++)
	{
		Student stu;
		stu.m_name = "选手";
		stu.m_name += seed[i];
		for (int j = 0; j < 3; j++)
		{
			stu.m_scores[j] = 0;
		}
		
		int uID = 100 + i;  //编号
		map.insert(make_pair(uID, stu));
		v.push_back(uID);
	}
	

}

//打乱顺序
void Set_random(vector<int>& v)
{
	random_shuffle(v.begin(), v.end());
}



//比赛打分，晋级
void Get_Scores(int index, map<int, Student>& map, vector<int>& v1, vector<int>& v2)
{
	srand(time(NULL));
	multimap<int, int,greater<int>> map_tmp;//定义一个临时multimap，用来存每个组6个人的分数、编号
	int flag_6 = 0;
	
	for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	{
		deque<int> d;
		for (int i = 0; i < 10; i++)
		{			
			d.push_back(rand() % 40 + 60);
		}
		sort(d.begin(), d.end());
		d.pop_front();
		d.pop_back();
		int Total=accumulate(d.begin(), d.end(),0);
		map.at(*it).m_scores[index-1] = Total / d.size();//将最后得分存到 map中

		map_tmp.insert(make_pair(Total / d.size(), *it));   //将分数和编号插入临时multimap
		flag_6++;		
		if (flag_6 ==6) //如果已经一组全部比完，开始进行淘汰，将前三名的编号存到v2中
		{
			int flag_3 = 0;
			for (multimap<int, int>::iterator itr = map_tmp.begin(); itr != map_tmp.end(); itr++)
			{
				v2.push_back((*itr).second);								
				flag_3++;
				if (flag_3 == 3)break;
			}

			flag_6 = 0;    //清空，以便存下一组的信息
			map_tmp.clear();
		}
			
	}
}


//显示结果
void Show_Results(int index, map<int, Student>& map, vector<int>& v)
{
	cout << "第一轮比赛结束,晋级选手为：" << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << " 选手：" << map.at(*it).m_name << "  得分：" << map.at(*it).m_scores[index-1] << endl;
	}
}


int main()
{

	map<int, Student> map1;
	vector<int> v1;
	vector<int> v2;
	vector<int> v3;
	vector<int> v4;

	//创建24名选手
	Init_Cadidate( map1, v1);


	//第一轮比赛


	//分组
	Set_random( v1);
	//比赛打分，淘汰，晋级
	Get_Scores( 1,map1,  v1, v2);
	//显示结果
	Show_Results( 1,map1,  v2);

	cout << "-----------------------------" << endl;

	//第二轮比赛

	//分组
	Set_random( v2);
	//比赛打分，淘汰，晋级
	Get_Scores(2,map1, v2, v3);
	//显示结果
	Show_Results( 2,map1,   v3);

	cout << "-----------------------------" << endl;

	//第三轮比赛

	//分组
	Set_random(  v3);
	//比赛打分，淘汰，晋级
	Get_Scores(3,map1,  v3,  v4);
	//显示结果
	Show_Results( 3, map1,   v4);

    return 0;
}


