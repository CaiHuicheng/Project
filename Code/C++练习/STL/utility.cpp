// pairģ������������������Ϊһ���µĶ��󣬸�������<utility>ͷ�ļ��ж���
// pairģ����֧�����²���
// pair<T1,T2> p1:����һ���յ�pair������������Ԫ�طֱ���T1��T2���ͣ�����ֵ��ʼ��
// pari<T1,T2> p1(v1,v2):����һ��pair������������Ԫ�طֱ���T1��T2���ͣ�����first��Ա��ʼ��Ϊv1��second��Ա��ʼ��Ϊv2
// make_pair(v1,v2):��v1��v2ֵ����һ���µ�pair������Ԫ�����ͷֱ���v1��v2������
// p1<p2�ֵ�������p1.first<p2.first����(p1.first>p2.first)&&(p1.second<p2.second),�򷵻�true
// p1==p2:�������pair�����first��second��Ա������ȣ����������������
// p.first/p.second:����p�е���Ϊfirst/second�Ĺ������ݳ�Ա 

//pair:���飬���Խ�����ֵ(first,second)��Ϊһ����Ԫ(pair)���Ǹ�ģ���ࡣ����map/multimap��������pairs������value/key�ĳɶ�Ԫ�ء��κκ�����Ҫ�ش�����ֵ��Ҳ��Ҫpair
/*
#include <utility>
#include <string>
#include <conio.h>
#include<iostream>
using namespace std;    
void test0()
{   
	pair<string,double> product1("tomatoes",3.25);//����һ���鵥Ԫ
	pair<string,double> product2;
	pair<string,double> product3;
	product2.first="lightbulbs";
	product2.second=0.99;//����pair��first��second����
	product3=make_pair("shoes",20.0);//make_pair�Ǹ�ģ�庯��������pair
	cout<<"the price of "<<product1.first<<" is $"<<product1.second<<endl;//��ȡpair��first��second������
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