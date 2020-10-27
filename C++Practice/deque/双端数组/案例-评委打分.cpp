#include<iostream>
#include<string>
#include<deque>
#include<vector>
#include<algorithm>//�㷨�ı�׼��
using namespace std;

//��ί���

//ѡ����
class Person {
public:
	Person(string name, int score) {
		this->m_Name = name;
		this->m_Score = score;
	}
	string m_Name;
	int m_Score;
};
//���
void setScore(vector<Person> &v) {
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
		//����ί��ķ��� ����deque������
		deque<int> d;
		for (int i = 0; i < 10; i++)
		{
			int score = rand() % 41 + 60;//60~100
			d.push_back(score);
		}
		//����
		sort(d.begin(), d.end());

		//ȥ����߷ֺ���ͷ�
		d.pop_back();
		d.pop_front();

		//ȡƽ����
		int sum = 0;
		for (deque<int>::iterator dit = d.begin(); dit != d.end(); dit++) {
			sum += *dit;
		}
		int avg = sum / d.size();

		//��ƽ���ָ�ֵ��ѡ��
		it->m_Score = avg;
	}
	
}
//��������ѡ��
void createPerson(vector<Person>&v) {
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5; i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		int score = 0;

		Person p(name, score);
		//��������ѡ�ַ�������
		v.push_back(p);
	}
}

void test01() {
	//1����������ѡ��
	vector<Person> v;
	createPerson(v);

	//2����������ѡ�֣���ί���� ��10�����ִ�ִ���deque������
	//3��sort�㷨��deque�����еķ����������� ȥ����߷ֺ���ͷ�
	//4��deque��������һ�� ��ʵ�ֳɼ��ۼ�
	//5����ȡƽ����
	setScore(v);
	
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++) {
		cout << (*it).m_Name << "\t������" << (*it).m_Score << endl;
	}
}

int main() {

	test01();

	system("pause");

	return 0;
}