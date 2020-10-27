#include<iostream>
using namespace std;
#include"speechManager.h"
#include<map>
#include<string>
#include<ctime>

int main() {
	//�������������
	SpeechManager sm;

	//���������
	srand((unsigned int)time(NULL));

	/*//����ѡ���Ƿ񴴽�
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << it->first<<it->second.m_Name<<it->second.m_Score << " ";
	}
	cout << endl;
	*/
	//���ڴ洢�û�ѡ��
	int choice = 0;

	while (true) {
		//��ʾ�˵�
		sm.show_Menu();
		cout << "����������ѡ��";
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴�����¼
			sm.loadRecord();
			sm.showRecord();
			break;
		case 3://��ձ�����¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");//����
			break;
		}
	}

	system("pause");
	return 0;
}