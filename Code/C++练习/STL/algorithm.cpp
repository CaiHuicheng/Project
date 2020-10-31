// 算法简介
// STL中提供能在各种容器中通用的算法，比如插入，删除，查找，排序等。大约有70中标准算法。
// 算法就是一个个函数模板
// 算法通过迭代器来操作容器中的元素。许多算法需要两个参数，一个是起始元素的迭代器，一个是终止元素的迭代器。比如，排序和查找
// 有的算法返回一个迭代器。比如find()算法，在容器中查找一个元素，并返回一个指向该元素的迭代器
// 算法可以处理容器，也可以处理数组
#include <algorithm>
#include <vector>
#include <conio.h>
#include<iostream>
using namespace std;    
//算法find
//template<class InIt, class T>InIt find(InIt first, InIt last, const T& val); //first 和 last 这两个参数都是容器的迭代器，它们给出了容器中的查找区间起点和终点。	这个区间是个左闭右开的区间，即区间的起点是位于查找范围之中的，而终点不是//	val参数是要查找的元素的值//函数返回值是一个迭代器。如果找到，则该迭代器指向被找到的元素。如果找不到，则该迭代器指向查找区间终点。
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