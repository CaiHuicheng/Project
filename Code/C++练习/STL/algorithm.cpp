// �㷨���
// STL���ṩ���ڸ���������ͨ�õ��㷨��������룬ɾ�������ң�����ȡ���Լ��70�б�׼�㷨��
// �㷨����һ��������ģ��
// �㷨ͨ�������������������е�Ԫ�ء�����㷨��Ҫ����������һ������ʼԪ�صĵ�������һ������ֹԪ�صĵ����������磬����Ͳ���
// �е��㷨����һ��������������find()�㷨���������в���һ��Ԫ�أ�������һ��ָ���Ԫ�صĵ�����
// �㷨���Դ���������Ҳ���Դ�������
#include <algorithm>
#include <vector>
#include <conio.h>
#include<iostream>
using namespace std;    
//�㷨find
//template<class InIt, class T>InIt find(InIt first, InIt last, const T& val); //first �� last �������������������ĵ����������Ǹ����������еĲ������������յ㡣	��������Ǹ�����ҿ������䣬������������λ�ڲ��ҷ�Χ֮�еģ����յ㲻��//	val������Ҫ���ҵ�Ԫ�ص�ֵ//��������ֵ��һ��������������ҵ�����õ�����ָ���ҵ���Ԫ�ء�����Ҳ�������õ�����ָ����������յ㡣
/*
void test0()
{  
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	vector<int>::iterator p;
	p=find(v.begin(),v.end(),3);
	if (p!=v.end())
	{
		cout<<*p<<endl;//3
	}
	p=find(v.begin(),v.end(),9);
	if (p==v.end())
	{
		cout<<"9 not found"<<endl;//9 not found
	}
	p=find(v.begin()+1,v.end()-2,1);
	if (p!=v.end())
	{
		cout<<*p<<endl;//3
	}
	int array[10]={10,20,30,40};
	int* pp=find(array,array+4,20);
	cout<<*pp<<endl;//20
}  
void Test(char h)
{
	cout<<"press key===="<<h<<endl;
	switch(h)
	{ 
	case '0':  test0();break; 
	case 27:
	case 'q':exit(0);break; 
	default:cout<<"default "<<h<<endl;break;
	}
}
void main()
{
	while(1)
	{
		Test(getch());
	} 
}
*/