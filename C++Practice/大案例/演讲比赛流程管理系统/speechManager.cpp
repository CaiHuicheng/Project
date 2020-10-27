#include"speechManager.h"

//���캯��
SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->GreateSpeaker();
}

//��ʾ����
void SpeechManager::show_Menu() {
	cout << "***************************************" << endl;
	cout << "*********�ݽ��������̹���ϵͳ**********" << endl;
	cout << "*********1����ʼ�ݽ�����     **********" << endl;
	cout << "*********2���鿴�����¼     **********" << endl;
	cout << "*********3����ձ�����¼     **********" << endl;
	cout << "*********0���˳�����ϵͳ     *********" << endl;
	cout << "***************************************" << endl;
}
//�˳�����
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
//����ѡ������
void SpeechManager::initSpeech() {
	//�����ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	this->m_Index = 1;
	//����¼������Ҳ���
	this->m_Record.clear();
}

//��ʼ����
void SpeechManager::startSpeech() {
	//��һ�ֱ���
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ��Ϣ
	this->showScore();
	//�ڶ��ֱ���
	this->m_Index++;
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechContest();
	//3����ʾ���ս��
	this->showScore();
	//4���������
	this->saveRecord();

	//���ñ�������ȡ��¼
	this->initSpeech();
	this->GreateSpeaker();
	this->loadRecord();

	cout << "�����������������" << endl;
	system("pause");
	system("cls");
}
//�ɼ���ǩ����
void SpeechManager::speechDraw() {
	cout << "�ڡ�" << this->m_Index << "��" << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "��ǩ���ݽ�˳������:" << endl;
	if (this->m_Index == 1) {
		//��һ��
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
			cout << *it << "\t";
		}
		cout << endl;
	}
	else {
		//�ڶ���
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
			cout << *it << "\t";
		}
		cout << endl;
	}
}

//����ѡ��
void SpeechManager::GreateSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		//��������ѡ��
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2 ; j++)
		{
			sp.m_Score[j] = 0;
		}

		//����ѡ�ֱ��
		this->v1.push_back(i + 10001);

		//ѡ�ֱ���Լ���Ӧѡ����Ϣ �ŵ�map��
		this->m_Speaker.insert(make_pair(i + 10001, sp));

	}
}

//����
void SpeechManager::speechContest() {
	cout << "----------------------��" << this->m_Index << "�ֱ�����ʼ��------------------------------" << endl;

	multimap<double, int, greater<double>> groupScore;//��ʱ���� ����key���� ��valueѡ�ֱ��

	int num = 0;//��¼��Ա�� 6 ��Ϊһ��
	vector<int> v_Src;//��������Ա����
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	//�������в�����Ա
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;

		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;//600~1000
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());//����
		d.pop_front();//ȥ��߷�
		d.pop_back();//ȥ��ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);//��ȡ�ܷ�
		double avg = sum / (double)d.size();//��ȡƽ����

		//ÿ����ƽ����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6��һ�� ����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "\t������" << this->m_Speaker[it->second].m_Name << "/t�ɼ���" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//ȡǰ����
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

	cout << "----------------------��" << this->m_Index << "�ֱ���������------------------------------" << endl;
	
	system("pause");
}

//��ʾ����
void SpeechManager::showScore() {
	cout << "----------------------��" << this->m_Index << "�ֽ���ѡ�����£�----------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "��ţ�" << *it << "\t������" <<m_Speaker[*it].m_Name << "/t�ɼ���" <<m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}
//��������
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//������ķ�ʽ���ļ�  --д�ļ�
	//��ÿ���˵���Ϣд���ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << ","
			<< m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	//�ر��ļ�
	ofs.close();
	cout << "�ļ��Ѿ�����" << endl;
	//�����ļ�״̬
	this->fileIsEmpty = false;
}
//��ȡ����
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);//���������� ��ȡ�ļ�
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ�������
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ� �Ż���
	string data;
	int index = 0;
	while (ifs >> data) {
		//cout << data << endl;
		vector<string> v;//���6���ַ�����Ϣ ǰ��������
		int pos = -1;//�鵽���ŵ�λ��
		int start = 0;
		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//û���ҵ�
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
		cout << "�ļ�Ϊ�պͲ�����!" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "��" << i + 1 << "��" <<
			"�ھ���ţ�" << this->m_Record[i][0] << "\t�÷֣�" << this->m_Record[i][1] <<
			"�Ǿ���ţ�" << this->m_Record[i][2] << "\t�÷֣�" << this->m_Record[i][3] <<
			"������ţ�" << this->m_Record[i][4] << "\t�÷֣�" << this->m_Record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽ ios::trunc �����������ļ����´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������
		this->initSpeech();
		//����ѡ��
		this->GreateSpeaker();
		//��ȡ�����¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

//��������
SpeechManager::~SpeechManager() {

}