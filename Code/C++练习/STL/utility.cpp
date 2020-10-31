// pair模板类用来绑定两个对象为一个新的对象，该类型在<utility>头文件中定义
// pair模板类支持如下操作
// pair<T1,T2> p1:创建一个空的pair对象，它的两个元素分别是T1和T2类型，采用值初始化
// pari<T1,T2> p1(v1,v2):创建一个pair对象，它的两个元素分别是T1和T2类型，其中first成员初始化为v1，second成员初始化为v2
// make_pair(v1,v2):以v1和v2值创建一个新的pair对象，其元素类型分别是v1和v2的类型
// p1<p2字典次序：如果p1.first<p2.first或者(p1.first>p2.first)&&(p1.second<p2.second),则返回true
// p1==p2:如果两个pair对象的first和second成员依次相等，则这两个对象相等
// p.first/p.second:返回p中的名为first/second的公有数据成员 

//pair:对组，可以将两个值(first,second)视为一个单元(pair)，是个模板类。对于map/multimap，就是用pairs来管理value/key的成对元素。任何函数需要回传两个值，也需要pair
/*
#include <utility>
#include <string>
#include <conio.h>
#include<iostream>
using namespace std;    
void test0()
{   
	pair<string,double> product1("tomatoes",3.25);//定义一个组单元
	pair<string,double> product2;
	pair<string,double> product3;
	product2.first="lightbulbs";
	product2.second=0.99;//设置pair的first，second数据
	product3=make_pair("shoes",20.0);//make_pair是个模板函数，返回pair
	cout<<"the price of "<<product1.first<<" is $"<<product1.second<<endl;//获取pair的first，second的数据
	cout<<"the price of "<<product2.first<<" is $"<<product2.second<<endl;
	cout<<"the price of "<<product3.first<<" is $"<<product3.second<<endl;
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
}*/