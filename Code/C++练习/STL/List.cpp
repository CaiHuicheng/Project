/*
#include <string>
#include <vector> 
#include <list>
#include <conio.h>
#include<iostream>
using namespace std;  
void PrintListInt(list<int>& param)
{
	for (list<int>::iterator iter=param.begin();iter!=param.end();iter++)
	{
		cout<<*iter<<" ";
	}
	cout<<endl;    
}
void PrintListString(list<string>& param)
{
	for (list<string>::iterator iter=param.begin();iter!=param.end();iter++)
	{
		cout<<*iter<<" ";
	}
	cout<<endl;    
}
//定义及初始化；没有返回值，或void
void test0()
{ 
	list<int> first(4);//定义并初始化4个0
	PrintListInt(first);//0 0 0 0
	list<int> second(3,88);//定义并初始化3个88
	PrintListInt(second);//88 88 88 
	first.assign(4,90);//assign赋值  //4个90
	second.assign(first.begin(),first.end());//second拷贝first
	int arr[]={23,45,56};
	second.assign(arr,arr+2);
	PrintListInt(second);//23 45 (没有56，者说明assign赋值是[begin,end),而不是[begin,end])
	second.assign(0,0);//清空second
	PrintListInt(second);//为空  
}
//增加删除元素；返回值是void,除erase()的返回值是iterator外
void test1()
{ 
	list<int> first(3,8);
	first.push_back(6);//增加一个元素在list末端
	first.push_front(2);//增加一个元素在list前端
	PrintListInt(first);//2 8 8 8 6
	first.pop_back();//删除list末端元素
	first.pop_front();//删除list前端元素
	PrintListInt(first);//8 8 8 
	first.insert(first.begin(),5);//在前端添加一个元素,不可以first.begin()+1;但vector<int>ve(4);ve.insert(ve.begin()+1,4);却可以
	first.insert(first.end(),2,9);//在末端添加两个元素，同上，end()-2不可以，但vector的end()-2可以
	PrintListInt(first);//5 8 8 8 9 9
	list<int>second;
	second.insert(second.end(),first.begin(),first.end());//second赋值first
	PrintListInt(second);//5 8 8 8 9 9

	second.erase(second.begin());//删除前端元素，参数不能为second.begin()+1,当然也不能为second.end();若要删除第二个元素，则可通过++second.begin(),或iterator，然后iterator++
	PrintListInt(second);//8 8 8 9 9 
	second.erase(second.begin(),second.end());//全部删除
	PrintListInt(second);//为空

	first.remove(77);//删除77这个不存在的元素 
	PrintListInt(first);//5 8 8 8 9 9
	first.remove(8);//删除所有的8这个元素
	PrintListInt(first);//5 9 9
	if (!first.empty()) 
		first.clear();//全部清除
	PrintListInt(first);//为空 
	//在list的函数insert(),erase()的函数参数时（iterator+2）是不可以的，只可以通过不停地iterator++；这一点与vector的insert(),erase()不同，可以通过iterator+2来很方便的删除任意位置的元素。因为它们存储的内存地址不一定连续的，所以不能通过iterator+、-N来访问第N个元素，只能通过iterator++来逐一访问,甚至量iterator=iterator+1都不行
	//由于list是双向链表，所以比线性表vector多提供了增加删除元素的函数，push_front(),pop_front(),remove(),remove_if()
}
//访问获取元素；返回值是Type T
void test2()
{ 
	list<int> first;
	for(int i=0;i<5;i++)
		first.push_back(i);
	cout<<first.front()<<endl;//0 返回前端元素的引用
	cout<<first.back()<<endl;//4 返回末端元素的引用
	//由于list是双向链表，所有没有像线性表vector那样提供下标索引，at()来提供方便的数据访问函数
}
//返回迭代器；返回值是iterator，或reverse_iterator
void test3()
{ 
	list<int> first;
	for(int i=0;i<5;i++)
		first.push_back(i); 
	cout<<*first.begin()<<endl;//0 不可以 cout<<*first.end()<<endl;不然会崩溃
	cout<<*first.rbegin()<<endl;//4 不可以cout<<*first.rend()<<endl;不然会崩溃
	for(list<int>::iterator it=first.begin();it!=first.end();it++)
		cout<<*it<<" ";//0 1 2 3 4
	cout<<endl;
	list<int>::reverse_iterator reIt=first.rbegin();
	while(reIt!=first.rend())
	{
		cout<<*reIt<<" ";//4 3 2 1 0
		reIt++;//记住是++，因为他是rbegin中的begin
	}
	cout<<endl;
	//与vector提供的函数相同begin(),end(),rbegin(),rend();不同的iterator不可以+N
} 
//其他
void test4()
{ 
	list<string> ve(2);
	cout<<ve.size()<<endl;//2 
	cout<<ve.max_size()<<endl;//134217727(string),10737441823(int)
	ve.resize(7);
	cout<<ve.size()<<endl;//7 
	//与vector不同的是少了capacity(),reserve()获取容量，设置容量

	list<int> first;
	for(int i=0;i<5;i++)
		first.push_back(i); 
	first.reverse();//逆序
	PrintListInt(first);//4 3 2 1 0
	list<int>second(2,9);
	second.swap(first);//两个list之间交互数据
	PrintListInt(first);//9 9
	PrintListInt(second);// 4 3 2 1 0
	first.sort();
	second.sort();//排序(从小到大)
	PrintListInt(second);//0 1 2 3 4
	first.merge(second);//second合并到first中，之后second为空。这里需要注意的是：在调用合并函数merge()之前，first和second都必须是从小到大的排序的
	PrintListInt(first);//0 1 2 3 4 9 9
	PrintListInt(second);//为空
	first.unique();//使唯一，删除相同的数据
	PrintListInt(first);//0 1 2 3 4 9
	//比vector多提供了逆序reverse(),排序sort(),和并merge()，使唯一unique()等数据处理的函数

	list<int> one,two;
	for(int i=0;i<4;i++)
	{
		one.push_back(i*5);//0 5 10 15
		two.push_back(i*10);//0 10 20 30 
	}
	one.splice(one.begin(),two);//在begin位置拼接整个two列表元素
	PrintListInt(one);//0 10 20 30 0 5 10 15
	PrintListInt(two);//为空
	two.assign(3,2);
	one.splice(one.begin(),two,two.begin());//在one列表的前端拼接two列表的一个前端元素
	PrintListInt(one);//2 0 10 20 30 0 5 10 15
	PrintListInt(two);//2 2
	one.splice(one.end(),two,two.begin(),two.end());//在one列表的end位置拼接整个two列表元素
	PrintListInt(two);//2 0 10 20 30 0 5 10 15 2 2
	PrintListInt(one);//为空
} 
//遍历list
void test5()
{ 
	list<int> vec;
	for (int i=0;i<10;i++)
	{
		vec.push_back(i);
	} 

	list<int>::iterator iter;
	for (iter=vec.begin();iter!=vec.end();iter++)
		cout<<*iter<<" ";
	cout<<endl;

	list<int>::reverse_iterator reIter;
	for (reIter=vec.rbegin();reIter!=vec.rend();reIter++) 
		cout<<*reIter<<" ";//9 8 7 6 5 4 3 2 1 0
	cout<<endl;

	vec.reverse();
	list<int>::reverse_iterator reveIter=vec.rbegin();
	while(reveIter!=vec.rend())
	{
		cout<<*reveIter<<" ";//0 1 2 3 4 5 6 7 8 9
		reveIter++;
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
	case '3':  test3();break;
	case '4':  test4();break;
	case '5':  test5();break; 
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