#include<iostream>
#include<string>
#include<deque>
#include<vector>
#include<algorithm>//算法的标准库
using namespace std;

//评委打分

//选手类
class Person {
public:
	Person(string name, int score) {
		this->m_Name = name;
		this->m_Score = score;
	}
	string m_Name;
	int m_Score;
};
//打分
void setScore(vector<Person> &v) {
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
		//将评委打的分数 放入deque容器中
		deque<int> d;
		for (int i = 0; i < 10; i++)
		{
			int score = rand() % 41 + 60;//60~100
			d.push_back(score);
		}
		//排序
		sort(d.begin(), d.end());

		//去除最高分和最低分
		d.pop_back();
		d.pop_front();

		//取平均分
		int sum = 0;
		for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++) {
			sum += *dit;
		}
		int avg = sum / d.size();

		//将平均分赋值给选手
		it->m_Score = avg;
	}
	
}
//创建五名选手
void createPerson(vector<Person>&v) {
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5; i++)
	{
		string name = "选手";
		name += nameSeed[i];
		int score = 0;

		Person p(name, score);
		//将创建的选手放入容器
		v.push_back(p);
	}
}

void test01() {
	//1、创建五名选手
	vector<Person> v;
	createPerson(v);

	//2、遍历五名选手，评委给分 把10个评分打分存在deque容器中
	//3、sort算法对deque容器中的分数进行排序 去掉最高分和最低分
	//4、deque容器遍历一遍 ，实现成绩累加
	//5、获取平均分
	setScore(v);
	
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
		cout << (*it).m_Name << "\t分数：" << (*it).m_Score << endl;
	}
}

int main() {

	test01();

	system("pause");

	return 0;
}