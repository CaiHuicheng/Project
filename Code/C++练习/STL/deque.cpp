/*
#include <string>
#include <deque> 
#include <vector>
#include <conio.h>
#include<iostream>
using namespace std;  
//定义及初始化；无返回值或void
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
	deque<int> d;//创建一个空的deque
	deque<int> de(2);//创建一个deque，含有2个缺省默认的数据0
	deque<int> deq(3,5);//创建一个含有3个5拷贝的deque
	deque<int> dequ(deq);//复制一个deque
	deque<int> first(dequ.begin(),dequ.end());//创建一个以[beg,end)区间的deque
	PrintDequeInt(first);//5 5 5
	d.assign(2,7);
	PrintDequeInt(d);//7 7
	de.assign(deq.begin(),deq.end());
	PrintDequeInt(de);//5 5 5
	//deque,list,vector的完全相同
}
//增加删除元素；返回值为void,除erase()的返回值为iterator外
void test1()
{  
	deque<string> first(2);//创建一个deque，含有2个缺省默认的数据" "
	cout<<first.at(0)<<" "<<first.at(1)<<" "<<endl;
	first.push_back("world");//在尾部加入一个数据
	first.push_front("hello ");//在头部插入一个数据
	first.pop_back();//删除最后一个数据
	first.pop_front();//删除头部数据
	 
	first.assign(1,"women");
	PrintDequeString(first);
	first.insert(first.begin()+1,"nihao");//在pos位置插入一个“nihao”；返回新数据的位置；注意pos位置要存在，eg:此begin()+2就不行，因为它表示第3个位置
	PrintDequeString(first); //women nihao
	first.insert(first.end(),2,"W");//注意他返回的是void
	PrintDequeString(first);//women nihao W W
	//first.insert(first.end(),first.begin(),first.end()); 不可以，当vector却可以 

	first.erase(first.begin());//删除pos位置的数据，返回下一个数据的位置
	PrintDequeString(first);//nihao W W
	first.erase(first.begin(),first.begin()+2);//删除[beg,end)区间的数据；放回下一个数据的位置
	PrintDequeString(first);//W
	first.clear();//删除容器中所有的的数据，可以用empty()来判断是否删除完
	//比vector多提供了pop_front()和push_front(),其他的完全相同
	//与list提供的函数完全相同，不过list的参数first.begin()不可以+1，+2，而deque却可以
}
//访问获取元素；返回值为TYPE T
void test2()
{  
	string str[]={"one","two","three","four","five","six"};
	deque<string> ve(str,str+6); 
	for(int i=0;i<6;i++) 
	{ 
		cout<<ve.at(i)<<" ";//使用at()通过i来进行访问，也不能越界。若越界，在调试时，会抛出异常；在运行时直接弹出错误
	}
	cout<<endl;
	cout<<ve.front()<<endl;//one //返回第一个元素的引用
	cout<<ve.back()<<endl;//six //返回最后一个元素的引用 
	//与vector完全相同，也提供了at()
	//比list多提供了一个访问元素的函数at()
}
//返回迭代器；返回值为iterator或reverse_iterator
void test3()
{  
	deque<int>ve(4);
	ve[0]=0;ve[1]=1;ve[2]=2;ve[3]=3;
	cout<<ve[0]<<" "<<ve[1]<<" "<<ve[2]<<" "<<ve[3]<<endl;
	deque<int>::iterator iter;//定义一个迭代器iter
	iter=ve.begin();//返回一个iterator，它指向deque第一个元素
	cout<<*iter<<endl;//0
	iter=ve.end();//返回一个iterator，它指向deque最末尾元素的下一个位置(它不是末尾元素)
	//cout<<*iter<<endl;//会出现错误
	cout<<*(iter-1)<<endl;//3 用此方法访问末尾元素
	deque<int>::reverse_iterator reIter;//定义一个反向的迭代器
	reIter=ve.rbegin();//返回一个方向iterator，它指向deque末尾元素
	cout<<*reIter<<endl;//3
	reIter=ve.rend();//返回一个方向iterator，它指向deque第一个元素之前的位置(它是不存在的)
	cout<<*(reIter-1)<<endl;//0  用此方法访问第一个元素
	//与vector提供的函数与用法完全相同
	//与list提供的函数相同，用法略有不同：list的iterator不可以加减n；deque却可以
} 
//其他
void test4()
{  
	deque<string> ve(8,"ss");
	cout<<ve.size()<<endl;//8
	cout<<ve.max_size()<<endl;//134217727，10737441823 
	ve.resize(2);//重置长度2	cout<<ve[2]<<endl;//会有问题因为[2]不存在	
	deque<string> de(4,"hh");
	de.swap(ve);//将de与ve元素互换
	cout<<ve.size()<<" "<<ve.front()<<endl;//4 hh
	cout<<de.size()<<" "<<de.front()<<endl;//2 ss
	//比vector少了获得容量函数capacity(),设置容量函数reserve()
	//比list少了sort(),merge(),remove(),remove_if(),reverse(),splice(),unique()
} 
//遍历deque
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
		cout<<*revIter<<" ";//0 1 2 3 4 5 6 7 8 //有点残缺
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
