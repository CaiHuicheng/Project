 //���������Ǹ����󣬵�������������ȥ�������ã�ʵ����Ҳִ���˺������� 
//�������󣺵��ò��������࣬����󳣳�Ϊ�������󣬼���������Ϊ�����ں����Ķ�������ͨ���������operator()��ʵ�ֵġ�eg:���� double d=average(3,2,3);�е�average����ʹ��ͨ������Ҳ�����Ǻ������� Average average�� 
/*
#include <conio.h>
#include<iostream>
using namespace std;    
double average(double a1,double a2,double a3){return (a1+a2+a3)/3;}
class Average
{
public:
	double operator()(double a1,double a2,double a3)//����()�����
	{
		return (a1+a2+a3)/3;
	}
};//����()�����ʱ����������ʹ������
void test0()
{ 
	Average avg;//��������
	cout<<avg(3,2,3)<<endl;//���2.66667 avg.operator(3,2,3)����������ȥ��������
	cout<<avg.operator()(3,2,3)<<endl;
} 
//����������ʹ��ģ�����ķ�ʽ
template<typename T> class MAverage
{
public:
	T operator()(T a1,T a2,T a3)//����()�����
	{
		return (a1+a2+a3)/3;
	}
};
//�ڱ�׼���У��������󱻹㷺��ʹ���Ի�õ��ԣ���׼���еĺܶ��㷨������ʹ�ú���������ߺ�������Ϊ�Զ��Ļص���Ϊ
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