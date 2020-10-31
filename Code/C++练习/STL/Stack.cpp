/*
#include <string>
#include <stack>
#include <queue> 
#include <conio.h>
#include<iostream>
using namespace std;   
//栈stack的用法
void test0()
{
	stack<int> st; 
	for (int i=0;i<4;i++)
		st.push(i*10); //压栈
	cout<<st.top()<<" "<<st.size()<<endl; //30 4
	for (int i=0;i<4;i++) 
	{
		cout<<st.top()<<" ";//30 20 10 0
		st.pop();//出栈
	}
	cout<<endl<<st.size()<<" "<<st.empty()<<endl;//0 1

	stack<int> first,scond;
	for (int i=0;i<5;i++)
	{
		first.push(i*5);
		scond.push(i*2);
	}
	first.swap(scond);//将栈first与scond元素互换
	first.emplace(444); //安放 它与push()的功能相同
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
	//栈stack，提供访问数据的接口只有一个top();而vector，list，deque则提供访问数的接口有：iterator，front(),back()；queue则提供的是back(),front(),没有iterator
}
//队列queue的用法
void test1()
{
	queue<int> q;
	for(int i=0;i<5;i++)
		q.push(i);//在队尾增加元素
	//返回元素数目，返回队头元素，返回队尾元素，是否为空
	cout<<q.size()<<" "<<q.front()<<" "<<q.back()<<" "<<q.empty()<<endl;//5 0 4 0
	q.pop();//删除队头元素
	cout<<q.front()<<" "<<q.back()<<endl;//1 4 

	queue<int> first,scond;
	for (int i=0;i<5;i++)
	{
		first.push(i*5);
		scond.push(i*2);
	}
	first.swap(scond);//将队列first与scond元素互换
	first.emplace(444); //安放 它与push()的功能相同
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
//优先队列priorityQueue的用法；插入的数据(按照某种顺序)自动排序
void test2()
{
	priority_queue<int>pq;
	pq.push(34);
	pq.push(21);
	pq.push(45);
	pq.push(9);
	//返回元素数目，返回队头元素，返回队尾元素，是否为空
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
	first.swap(scond);//将优先队列first与scond元素互换
	first.emplace(444); //安放 它与push()的功能相同
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
容器适配器：是用基本的容器改造出的容器。共有的成员函数：empty(),size(),push(),pop(),(front(),back()/top()),swap(),emplace()
栈stack：是先进后出(FILO)的数据结构，可用vector，list，deque来实现，默认用deque实现。只能插入push()，删除pop()，访问栈顶元素top()
队列queue：是先进先出(FIFO)的数据结构，可用list，deque来实现，默认用deque实现。也提供了push(),pop()但是push()发生在队尾，pop()发生在队头。与stack不同的是top()变成了(front(),back())返回队头元素front(),返回队尾元素back(),
优先队列priority_queue：可用vector，deque实现，默认用vector实现。插入到容器中的元素自动排序(从大到小)，这些元素是有优先级的，大的在前小的在后，与queue不同的是由front(),back()变成一个top()
*/
/************************************************************************/