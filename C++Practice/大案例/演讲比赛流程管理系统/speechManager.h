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

	//���캯��
	SpeechManager();

	//��ʾ�˵�
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��������
	~SpeechManager();

	//��ʼ��
	void initSpeech();

	//����ѡ��
	void GreateSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ�����ķ���
	void showScore();
	//�������
	void saveRecord();
	//��ȡ����
	void loadRecord();
	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;
	//�������ɼ�����
	map<int, vector<string>> m_Record;
	//�鿴����ɼ�
	void showRecord();
	//��ռ�¼
	void clearRecord();

	//����ѡ�� ���� 12��
	vector<int> v1;
	//��һ�ֽ��������� 6��
	vector<int> v2;
	//ʤ����ǰ���� 3 ��
	vector<int> vVictory;
	//��ű�� �Լ���Ӧ�ľ���ѡ�� ����
	map<int, Speaker> m_Speaker;
	//��¼��������
	int m_Index;
};

