/*
#include <string>
#include <deque> 
#include <vector>
#include <conio.h>
#include<iostream>
using namespace std;  
//���弰��ʼ�����޷���ֵ��void
void PrintDequeInt(deque<int> param)
{
	for (deque<int>::iterator iter=param.begin();iter!=param.end();iter++)
	{
		cout<<*iter<<" ";
	}
	cout<<endl;	
}
void PrintDequeString(deque<string> param)
{
	for (deque<string>::iterator iter=param.begin();iter!=param.end();iter++)
	{
		cout<<*iter<<" ";
	}
	cout<<endl;	
}
void test0()
{  
	deque<int> d;//����һ���յ�deque
	deque<int> de(2);//����һ��deque������2��ȱʡĬ�ϵ�����0
	deque<int> deq(3,5);//����һ������3��5������deque
	deque<int> dequ(deq);//����һ��deque
	deque<int> first(dequ.begin(),dequ.end());//����һ����[beg,end)�����deque
	PrintDequeInt(first);//5 5 5
	d.assign(2,7);
	PrintDequeInt(d);//7 7
	de.assign(deq.begin(),deq.end());
	PrintDequeInt(de);//5 5 5
	//deque,list,vector����ȫ��ͬ
}
//����ɾ��Ԫ�أ�����ֵΪvoid,��erase()�ķ���ֵΪiterator��
void test1()
{  
	deque<string> first(2);//����һ��deque������2��ȱʡĬ�ϵ�����" "
	cout<<first.at(0)<<" "<<first.at(1)<<" "<<endl;
	first.push_back("world");//��β������һ������
	first.push_front("hello ");//��ͷ������һ������
	first.pop_back();//ɾ�����һ������
	first.pop_front();//ɾ��ͷ������
	 
	first.assign(1,"women");
	PrintDequeString(first);
	first.insert(first.begin()+1,"nihao");//��posλ�ò���һ����nihao�������������ݵ�λ�ã�ע��posλ��Ҫ���ڣ�eg:��begin()+2�Ͳ��У���Ϊ����ʾ��3��λ��
	PrintDequeString(first); //women nihao
	first.insert(first.end(),2,"W");//ע�������ص���void
	PrintDequeString(first);//women nihao W W
	//first.insert(first.end(),first.begin(),first.end()); �����ԣ���vectorȴ���� 

	first.erase(first.begin());//ɾ��posλ�õ����ݣ�������һ�����ݵ�λ��
	PrintDequeString(first);//nihao W W
	first.erase(first.begin(),first.begin()+2);//ɾ��[beg,end)��������ݣ��Ż���һ�����ݵ�λ��
	PrintDequeString(first);//W
	first.clear();//ɾ�����������еĵ����ݣ�������empty()���ж��Ƿ�ɾ����
	//��vector���ṩ��pop_front()��push_front(),��������ȫ��ͬ
	//��list�ṩ�ĺ�����ȫ��ͬ������list�Ĳ���first.begin()������+1��+2����dequeȴ����
}
//���ʻ�ȡԪ�أ�����ֵΪTYPE T
void test2()
{  
	string str[]={"one","two","three","four","five","six"};
	deque<string> ve(str,str+6); 
	for(int i=0;i<6;i++) 
	{ 
		cout<<ve.at(i)<<" ";//ʹ��at()ͨ��i�����з��ʣ�Ҳ����Խ�硣��Խ�磬�ڵ���ʱ�����׳��쳣��������ʱֱ�ӵ�������
	}
	cout<<endl;
	cout<<ve.front()<<endl;//one //���ص�һ��Ԫ�ص�����
	cout<<ve.back()<<endl;//six //�������һ��Ԫ�ص����� 
	//��vector��ȫ��ͬ��Ҳ�ṩ��at()
	//��list���ṩ��һ������Ԫ�صĺ���at()
}
//���ص�����������ֵΪiterator��reverse_iterator
void test3()
{  
	deque<int>ve(4);
	ve[0]=0;ve[1]=1;ve[2]=2;ve[3]=3;
	cout<<ve[0]<<" "<<ve[1]<<" "<<ve[2]<<" "<<ve[3]<<endl;
	deque<int>::iterator iter;//����һ��������iter
	iter=ve.begin();//����һ��iterator����ָ��deque��һ��Ԫ��
	cout<<*iter<<endl;//0
	iter=ve.end();//����һ��iterator����ָ��deque��ĩβԪ�ص���һ��λ��(������ĩβԪ��)
	//cout<<*iter<<endl;//����ִ���
	cout<<*(iter-1)<<endl;//3 �ô˷�������ĩβԪ��
	deque<int>::reverse_iterator reIter;//����һ������ĵ�����
	reIter=ve.rbegin();//����һ������iterator����ָ��dequeĩβԪ��
	cout<<*reIter<<endl;//3
	reIter=ve.rend();//����һ������iterator����ָ��deque��һ��Ԫ��֮ǰ��λ��(���ǲ����ڵ�)
	cout<<*(reIter-1)<<endl;//0  �ô˷������ʵ�һ��Ԫ��
	//��vector�ṩ�ĺ������÷���ȫ��ͬ
	//��list�ṩ�ĺ�����ͬ���÷����в�ͬ��list��iterator�����ԼӼ�n��dequeȴ����
} 
//����
void test4()
{  
	deque<string> ve(8,"ss");
	cout<<ve.size()<<endl;//8
	cout<<ve.max_size()<<endl;//134217727��10737441823 
	ve.resize(2);//���ó���2	cout<<ve[2]<<endl;//����������Ϊ[2]������	
	deque<string> de(4,"hh");
	de.swap(ve);//��de��veԪ�ػ���
	cout<<ve.size()<<" "<<ve.front()<<endl;//4 hh
	cout<<de.size()<<" "<<de.front()<<endl;//2 ss
	//��vector���˻����������capacity(),������������reserve()
	//��list����sort(),merge(),remove(),remove_if(),reverse(),splice(),unique()
} 
//����deque
void test5()
{  
	deque<int> vec;
	for (int i=0;i<10;i++)
	{
		vec.push_back(i);
	}
	for (int i=0;i<vec.size();i++) 
		cout<<vec[i]<<" ";
	cout<<endl;

	deque<int>::iterator iter;
	for (iter=vec.begin();iter!=vec.end();iter++)
		cout<<*iter<<" ";
	cout<<endl;

	deque<int>::reverse_iterator reIter;
	for (reIter=vec.rbegin();reIter!=vec.rend();reIter++) 
		cout<<*reIter<<" ";//9 8 7 6 5 4 3 2 1 0
	cout<<endl;

	deque<int>::reverse_iterator revIter;
	for (revIter=vec.rend()-1;revIter!=vec.rbegin();revIter--) 
		cout<<*revIter<<" ";//0 1 2 3 4 5 6 7 8 //�е��ȱ
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
