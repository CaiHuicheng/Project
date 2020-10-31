 //函数对象：是个对象，但是用起来看上去像函数调用，实际上也执行了函数调用 
//函数对象：调用操作符的类，其对象常称为函数对象，即它们是行为类似于函数的对象。它是通过重载类的operator()来实现的。eg:对于 double d=average(3,2,3);中的average可以使普通函数，也可以是函数对象 Average average； 
/*
#include <conio.h>
#include<iostream>
using namespace std;    
double average(double a1,double a2,double a3){return (a1+a2+a3)/3;}
class Average
{
public:
	double operator()(double a1,double a2,double a3)//重载()运算符
	{
		return (a1+a2+a3)/3;
	}
};//重载()运算符时，参数可以使任意多个
void test0()
{ 
	Average avg;//函数对象
	cout<<avg(3,2,3)<<endl;//输出2.66667 avg.operator(3,2,3)用起来看上去像函数调用
	cout<<avg.operator()(3,2,3)<<endl;
} 
//大多情况下是使用模板的类的方式
template<typename T> class MAverage
{
public:
	T operator()(T a1,T a2,T a3)//重载()运算符
	{
		return (a1+a2+a3)/3;
	}
};
//在标准库中，函数对象被广泛的使用以获得弹性，标准库中的很多算法都可以使用函数对象或者函数来作为自定的回调行为
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