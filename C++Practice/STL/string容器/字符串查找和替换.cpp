#include<iostream>
#include<string>
using namespace std;

//string ���Һ��滻

void test01() {
	string str1 = "hello world";
	//�ж�δ�ҵ��ַ���
	if (str1.find("o")==-1)
	{
		cout << "δ�ҵ�ָ���ַ���" << endl;
	}
	else
	{
		cout << "pos=" << str1.find("o") << endl;//���ء�o�����±�
	}

	int pos = str1.rfind("o");//find����������  rfind ����������

	cout << "pos=" << pos << endl;//���ء�o�����±�
	
}

void test02() {
	string str1 = "abcdefg";
	str1.replace(1, 3, "1111");
	cout << "str1=" << str1 << endl;
}

int main() {
	//test01();
	test02();
	system("pause");
	return 0;
}