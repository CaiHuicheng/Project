/*
#include <string>
#include <stack>
#include <queue> 
#include <conio.h>
#include<iostream>
using namespace std;   
//ջstack���÷�
void test0()
{
	stack<int> st; 
	for (int i=0;i<4;i++)
		st.push(i*10); //ѹջ
	cout<<st.top()<<" "<<st.size()<<endl; //30 4
	for (int i=0;i<4;i++) 
	{
		cout<<st.top()<<" ";//30 20 10 0
		st.pop();//��ջ
	}
	cout<<endl<<st.size()<<" "<<st.empty()<<endl;//0 1

	stack<int> first,scond;
	for (int i=0;i<5;i++)
	{
		first.push(i*5);
		scond.push(i*2);
	}
	first.swap(scond);//��ջfirst��scondԪ�ػ���
	first.emplace(444); //���� ����push()�Ĺ�����ͬ
	scond.emplace(852);

	while (!first.empty())
	{
		cout<<first.top()<<" ";//444 8 6 4 2 0
		first.pop();
	}
	cout<<endl;
	while (!scond.empty())
	{
		cout<<scond.top()<<" ";//852 20 15 10 5 0
		scond.pop();
	}
	cout<<endl;	 
	//ջstack���ṩ�������ݵĽӿ�ֻ��һ��top();��vector��list��deque���ṩ�������Ľӿ��У�iterator��front(),back()��queue���ṩ����back(),front(),û��iterator
}
//����queue���÷�
void test1()
{
	queue<int> q;
	for(int i=0;i<5;i++)
		q.push(i);//�ڶ�β����Ԫ��
	//����Ԫ����Ŀ�����ض�ͷԪ�أ����ض�βԪ�أ��Ƿ�Ϊ��
	cout<<q.size()<<" "<<q.front()<<" "<<q.back()<<" "<<q.empty()<<endl;//5 0 4 0
	q.pop();//ɾ����ͷԪ��
	cout<<q.front()<<" "<<q.back()<<endl;//1 4 

	queue<int> first,scond;
	for (int i=0;i<5;i++)
	{
		first.push(i*5);
		scond.push(i*2);
	}
	first.swap(scond);//������first��scondԪ�ػ���
	first.emplace(444); //���� ����push()�Ĺ�����ͬ
	scond.emplace(852);

	while (!first.empty())
	{
		cout<<first.front()<<" ";//0 2 4 6 8 444
		first.pop();
	}
	cout<<endl;
	while (!scond.empty())
	{
		cout<<scond.front()<<" ";//0 5 10 15 20 852
		scond.pop();
	}
	cout<<endl;
}
//���ȶ���priorityQueue���÷������������(����ĳ��˳��)�Զ�����
void test2()
{
	priority_queue<int>pq;
	pq.push(34);
	pq.push(21);
	pq.push(45);
	pq.push(9);
	//����Ԫ����Ŀ�����ض�ͷԪ�أ����ض�βԪ�أ��Ƿ�Ϊ��
	cout<<pq.size()<<" "<<pq.top()<<" "<<pq.empty()<<endl;//4 45 0
	while(!pq.empty())
	{
		cout<<pq.top()<<" ";//45 34 21 9
		pq.pop();
	}
	cout<<endl; 
	priority_queue<int> first,scond;
	for (int i=0;i<5;i++)
	{
		first.push(i*5);
		scond.push(i*2);
	}
	first.swap(scond);//�����ȶ���first��scondԪ�ػ���
	first.emplace(444); //���� ����push()�Ĺ�����ͬ
	scond.emplace(852);

	while (!first.empty())
	{
		cout<<first.top()<<" ";//444 8 6 4 2 0
		first.pop();
	}
	cout<<endl;
	while (!scond.empty())
	{
		cout<<scond.top()<<" ";//852 20 15 10 5 0
		scond.pop();
	}
	cout<<endl;
}
void Test(char h)
{
	cout<<"press key===="<<h<<endl;
	switch(h)
	{ 
	case '0':  test0();break;
 	case '1':  test1();break;
 	case '2':  test2();break; 
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
/************************************************************************/
/* 
���������������û�������������������������еĳ�Ա������empty(),size(),push(),pop(),(front(),back()/top()),swap(),emplace()
ջstack�����Ƚ����(FILO)�����ݽṹ������vector��list��deque��ʵ�֣�Ĭ����dequeʵ�֡�ֻ�ܲ���push()��ɾ��pop()������ջ��Ԫ��top()
����queue�����Ƚ��ȳ�(FIFO)�����ݽṹ������list��deque��ʵ�֣�Ĭ����dequeʵ�֡�Ҳ�ṩ��push(),pop()����push()�����ڶ�β��pop()�����ڶ�ͷ����stack��ͬ����top()�����(front(),back())���ض�ͷԪ��front(),���ض�βԪ��back(),
���ȶ���priority_queue������vector��dequeʵ�֣�Ĭ����vectorʵ�֡����뵽�����е�Ԫ���Զ�����(�Ӵ�С)����ЩԪ���������ȼ��ģ������ǰС���ں���queue��ͬ������front(),back()���һ��top()
*/
/************************************************************************/