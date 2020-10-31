//文件名:CHAPTER6-1.cpp
/*
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>  
#include <stdlib.h>   
using namespace std;  
void test0()
{
    vector<string> myVector;
    cout<<"Good"<<endl;
}
void test1()
{ 
    vector<string> myVector;
    myVector.push_back("chocolate");
    myVector.push_back("Strawberry");
    myVector.push_back("Lime");
    myVector.push_back("vanilla");
	
    for (int i=0;i<4;i++)
    {
        cout<<myVector[i]<<" ";
    }
    cout<<endl;
	if (!myVector.empty())
	{
		cout<<"no empty"<<endl;
	}
}
void test2()//有问题
{ 
    vector<int> myVector;
    myVector.reserve(5);//有问题
    myVector.resize(5);
    for (int i=0;i<5;i++)
    {
        myVector[i]=i;
        cout<<myVector[i]<<"  ";
    }
    cout<<endl;
}
void test3()
{ 
    typedef vector<int> INTVECTOR;
    INTVECTOR theVector;
    theVector.push_back(42);
    cout<<"size is:"<<theVector.size()<<endl;
    cout<<"maximum size is:"<<theVector.max_size()<<endl;
    cout<<"capacity is:"<<theVector.capacity()<<endl;
    theVector.reserve(100);
    cout << endl << "After reserving storage for 1000 elements:" << endl;
    cout<<"size is:"<<theVector.size()<<endl;
    cout<<"maximum size is:"<<theVector.max_size()<<endl;
    cout<<"capacity is:"<<theVector.capacity()<<endl;
    theVector.resize(2000);
    cout << endl << "After resizing storage to 2000 elements:" << endl;
    cout<<"size is:"<<theVector.size()<<endl;
    cout<<"maximum size is:"<<theVector.max_size()<<endl;
    cout<<"capacity is:"<<theVector.capacity()<<endl;
}
void test4()
{ 
	vector<char>myVector;
	for (int i=0;i<5;i++)
	{
		myVector.push_back(char((char)i));
	}
	vector<char>::iterator  iter;
	for (iter=myVector.begin();iter!=myVector.end();iter++)
	{
		cout<<*iter;
		if (iter!=myVector.end()-1)
		{
			cout<<", ";
		}
	}
	cout<<endl;
	cout<<"size:"<<myVector.size()<<endl;
	myVector.pop_back();
	cout<<"size:"<<myVector.size()<<endl;
	myVector.erase(myVector.begin());
	cout<<"size:"<<myVector.size()<<endl;
	myVector.erase(myVector.begin(),myVector.end());
	cout<<"size:"<<myVector.size()<<endl;
}
#include <algorithm> 
void PrintIt (char* &stringToPrint) {cout<<stringToPrint<<endl;}
void test5()
{ 
	vector<char*>fruitVector;
	fruitVector.push_back("carrot");
	fruitVector.push_back("pupkin");
	fruitVector.push_back("potato");
	fruitVector.push_back("apple");
	for_each(fruitVector.begin(),fruitVector.end(),PrintIt);
}
void test6()
{ 
	vector<int>scores;
	scores.push_back(100);
	scores.push_back(80);
	scores.push_back(20);
	scores.push_back(99);
	scores.push_back(100);
	int numOf100(0);
	numOf100=count(scores.begin(),scores.end(),100);
	cout<<"there were "<<numOf100<<" scores of 100"<<endl;
	vector<int>::iterator iter;
	iter=find(scores.begin(),scores.end(),20);
	if (iter==scores.end())
	{
		cout<<"20 is not found in vector."<<endl;
	}
	else
	{
		cout<<*iter<<endl;
	}
}
const string ToothbrushCode("0003");
class IsAToothbrush 
{
public:  
	bool operator() ( string& SalesRecord )
	{
		return SalesRecord.substr(0,4)==ToothbrushCode;
	}     
};
void test7()
{ 
	vector<string> SalesRecords;
	SalesRecords.push_back("0001 Soap");
	SalesRecords.push_back("0002 Shampoo");
	//SalesRecords.push_back("0003 Toothbrush");
	SalesRecords.push_back("0004 Toothpaste");
	SalesRecords.push_back("0003 Toothbrush");
	int NumberOfToothbrushes(0);  
	NumberOfToothbrushes=count_if(SalesRecords.begin(),SalesRecords.end(),IsAToothbrush());
	cout << "There were " << NumberOfToothbrushes << " toothbrushes sold" << endl;

	vector<string>::iterator iter=find_if(SalesRecords.begin(),SalesRecords.end(),IsAToothbrush());
	if (iter==SalesRecords.end())//有点小问题
	{
		cout<<"toothbrushes is found"<<endl;
	}
	else
	{
		cout<<"toothbrushes is not found"<<endl;
	}
}
class IsAToothbrushDD 
{
public:  
	IsAToothbrushDD(string& ToothbrushCodeCC) : ToothbrushCodeDD(ToothbrushCodeCC){}
	bool operator() ( string& SalesRecord )
	{
		return SalesRecord.substr(0,4)==ToothbrushCode;
	}     
private:
	string ToothbrushCodeDD;
};
void test8()
{ 
	vector<string> SalesRecords;
	SalesRecords.push_back("0001 Soap");
	SalesRecords.push_back("0002 Shampoo");
	SalesRecords.push_back("0003 Toothbrush");
	SalesRecords.push_back("0004 Toothpaste");
	SalesRecords.push_back("0003 Toothbrush");
	string VariableToothbrushCodeDD("0003");
	int NumberOfToothbrushes(0);  
	NumberOfToothbrushes=count_if(SalesRecords.begin(),SalesRecords.end(),IsAToothbrushDD(VariableToothbrushCodeDD));
	cout << "There were " << NumberOfToothbrushes << " toothbrushes sold" << endl;
}
void test9()
{ 
	int * p=new int(2);
	cout<<*p<<endl;
	cout<<"p dizhi:"<<p<<" "<<&(*p)<<endl;
}
void testa()
{ 
}
void testb()
{ 
}
void testc()
{ 
}
void testd()
{ 
}
void teste()
{ 
}
void testf()
{ 
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
    case '6':  test6();break;
    case '7':  test7();break;
    case '8':  test8();break;
    case '9':  test9();break;
    case 27:
    case 'q':exit(0);break; 
    default:cout<<"default "<<h<<endl;break;
    }
}
#include <conio.h>
void main()
{
    while(1)
    {
        Test(getch());
    } 
    
}
*/