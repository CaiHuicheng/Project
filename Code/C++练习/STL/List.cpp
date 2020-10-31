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
//���弰��ʼ����û�з���ֵ����void
void test0()
{ 
	list<int> first(4);//���岢��ʼ��4��0
	PrintListInt(first);//0 0 0 0
	list<int> second(3,88);//���岢��ʼ��3��88
	PrintListInt(second);//88 88 88 
	first.assign(4,90);//assign��ֵ  //4��90
	second.assign(first.begin(),first.end());//second����first
	int arr[]={23,45,56};
	second.assign(arr,arr+2);
	PrintListInt(second);//23 45 (û��56����˵��assign��ֵ��[begin,end),������[begin,end])
	second.assign(0,0);//���second
	PrintListInt(second);//Ϊ��  
}
//����ɾ��Ԫ�أ�����ֵ��void,��erase()�ķ���ֵ��iterator��
void test1()
{ 
	list<int> first(3,8);
	first.push_back(6);//����һ��Ԫ����listĩ��
	first.push_front(2);//����һ��Ԫ����listǰ��
	PrintListInt(first);//2 8 8 8 6
	first.pop_back();//ɾ��listĩ��Ԫ��
	first.pop_front();//ɾ��listǰ��Ԫ��
	PrintListInt(first);//8 8 8 
	first.insert(first.begin(),5);//��ǰ�����һ��Ԫ��,������first.begin()+1;��vector<int>ve(4);ve.insert(ve.begin()+1,4);ȴ����
	first.insert(first.end(),2,9);//��ĩ���������Ԫ�أ�ͬ�ϣ�end()-2�����ԣ���vector��end()-2����
	PrintListInt(first);//5 8 8 8 9 9
	list<int>second;
	second.insert(second.end(),first.begin(),first.end());//second��ֵfirst
	PrintListInt(second);//5 8 8 8 9 9

	second.erase(second.begin());//ɾ��ǰ��Ԫ�أ���������Ϊsecond.begin()+1,��ȻҲ����Ϊsecond.end();��Ҫɾ���ڶ���Ԫ�أ����ͨ��++second.begin(),��iterator��Ȼ��iterator++
	PrintListInt(second);//8 8 8 9 9 
	second.erase(second.begin(),second.end());//ȫ��ɾ��
	PrintListInt(second);//Ϊ��

	first.remove(77);//ɾ��77��������ڵ�Ԫ�� 
	PrintListInt(first);//5 8 8 8 9 9
	first.remove(8);//ɾ�����е�8���Ԫ��
	PrintListInt(first);//5 9 9
	if (!first.empty()) 
		first.clear();//ȫ�����
	PrintListInt(first);//Ϊ�� 
	//��list�ĺ���insert(),erase()�ĺ�������ʱ��iterator+2���ǲ����Եģ�ֻ����ͨ����ͣ��iterator++����һ����vector��insert(),erase()��ͬ������ͨ��iterator+2���ܷ����ɾ������λ�õ�Ԫ�ء���Ϊ���Ǵ洢���ڴ��ַ��һ�������ģ����Բ���ͨ��iterator+��-N�����ʵ�N��Ԫ�أ�ֻ��ͨ��iterator++����һ����,������iterator=iterator+1������
	//����list��˫���������Ա����Ա�vector���ṩ������ɾ��Ԫ�صĺ�����push_front(),pop_front(),remove(),remove_if()
}
//���ʻ�ȡԪ�أ�����ֵ��Type T
void test2()
{ 
	list<int> first;
	for(int i=0;i<5;i++)
		first.push_back(i);
	cout<<first.front()<<endl;//0 ����ǰ��Ԫ�ص�����
	cout<<first.back()<<endl;//4 ����ĩ��Ԫ�ص�����
	//����list��˫����������û�������Ա�vector�����ṩ�±�������at()���ṩ��������ݷ��ʺ���
}
//���ص�����������ֵ��iterator����reverse_iterator
void test3()
{ 
	list<int> first;
	for(int i=0;i<5;i++)
		first.push_back(i); 
	cout<<*first.begin()<<endl;//0 ������ cout<<*first.end()<<endl;��Ȼ�����
	cout<<*first.rbegin()<<endl;//4 ������cout<<*first.rend()<<endl;��Ȼ�����
	for(list<int>::iterator it=first.begin();it!=first.end();it++)
		cout<<*it<<" ";//0 1 2 3 4
	cout<<endl;
	list<int>::reverse_iterator reIt=first.rbegin();
	while(reIt!=first.rend())
	{
		cout<<*reIt<<" ";//4 3 2 1 0
		reIt++;//��ס��++����Ϊ����rbegin�е�begin
	}
	cout<<endl;
	//��vector�ṩ�ĺ�����ͬbegin(),end(),rbegin(),rend();��ͬ��iterator������+N
} 
//����
void test4()
{ 
	list<string> ve(2);
	cout<<ve.size()<<endl;//2 
	cout<<ve.max_size()<<endl;//134217727(string),10737441823(int)
	ve.resize(7);
	cout<<ve.size()<<endl;//7 
	//��vector��ͬ��������capacity(),reserve()��ȡ��������������

	list<int> first;
	for(int i=0;i<5;i++)
		first.push_back(i); 
	first.reverse();//����
	PrintListInt(first);//4 3 2 1 0
	list<int>second(2,9);
	second.swap(first);//����list֮�佻������
	PrintListInt(first);//9 9
	PrintListInt(second);// 4 3 2 1 0
	first.sort();
	second.sort();//����(��С����)
	PrintListInt(second);//0 1 2 3 4
	first.merge(second);//second�ϲ���first�У�֮��secondΪ�ա�������Ҫע����ǣ��ڵ��úϲ�����merge()֮ǰ��first��second�������Ǵ�С����������
	PrintListInt(first);//0 1 2 3 4 9 9
	PrintListInt(second);//Ϊ��
	first.unique();//ʹΨһ��ɾ����ͬ������
	PrintListInt(first);//0 1 2 3 4 9
	//��vector���ṩ������reverse(),����sort(),�Ͳ�merge()��ʹΨһunique()�����ݴ���ĺ���

	list<int> one,two;
	for(int i=0;i<4;i++)
	{
		one.push_back(i*5);//0 5 10 15
		two.push_back(i*10);//0 10 20 30 
	}
	one.splice(one.begin(),two);//��beginλ��ƴ������two�б�Ԫ��
	PrintListInt(one);//0 10 20 30 0 5 10 15
	PrintListInt(two);//Ϊ��
	two.assign(3,2);
	one.splice(one.begin(),two,two.begin());//��one�б��ǰ��ƴ��two�б��һ��ǰ��Ԫ��
	PrintListInt(one);//2 0 10 20 30 0 5 10 15
	PrintListInt(two);//2 2
	one.splice(one.end(),two,two.begin(),two.end());//��one�б��endλ��ƴ������two�б�Ԫ��
	PrintListInt(two);//2 0 10 20 30 0 5 10 15 2 2
	PrintListInt(one);//Ϊ��
} 
//����list
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