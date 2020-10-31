//关联容器，通过 键 存储和读取元素。顺序容器，通过元素在容器中的位置顺序存储和读取元素。
//关联容器和顺序容器的本质差别在于：关联容器通过键（key）存储和读取元素，而顺序容器则通过元素在容器中的位置顺序存储和访问元素。
/*
map是标准关联式容器之一，一个map是一个键值对序列，即(key，value)对。它提供了基于key的快速检索能力，在一个map中key值是唯一的。map提供了双向迭代器，即从前往后的(iterator)，也有从后往前的(reverse_iterator)。
map要求能对key进行操作，且保持按key值递增有序，因此map上的迭代器也是递增有序的。如果对于元素并不需要保持有序，可以使用hash_map。
map中key值是唯一的，如果map中已存在一个键值对(昵称，密码):("sky",789852)，而我们还是想插入一个键值对("sky",789852)则会报错(不是报错，准确的说是，返回插入不成功！)。而我们有的确想这样做，即一个键对于多个值，幸运的是multimap可以实现这个功能。

map是一类关联容器。它的特点是增加和删除节点对迭代器的影响很小，除了那个操作节点，对其他节点都没有什么影响。因为它内部结构式红黑二叉树。对于迭代器来说可以修改实值value，而不能修改关键字key。
map的功能
自动建立key-value的对应。key和value可以使任意你需要的类型。
根据key值快速查找记录，查找的复杂度基本是log(N)
快速插入key-value记录
快速删除记录
根据key修改value记录
遍历所有记录
*/
/*
#include <string>
#include <map>  
#include <conio.h>
#include<iostream>
using namespace std;   
//定义及初始化；没有返回值，或void
void test0()
{  
	multimap<int,string> first;
	first.insert(pair<int,string>(3,"hello"));
	multimap<int,string> second(first);//拷贝构造函数
	multimap<int,string> third(first.begin(),first.end());//区间构造函数
}
//增加删除元素；返回值是void,除erase()的返回值是iterator外
void test1()
{ 	 
	//first insert 用insert()函数插入pair数据
	multimap<char,int> myfirst;
	myfirst.insert(pair<char,int>('a',100)); 
	//second insert 用insert()函数插入value_type数据
	myfirst.insert(map<char,int>::value_type('f',50)); //可以用map<char,int>也可以用multimap<char,int>
	myfirst.insert(map<char,int>::value_type('f',60));  
// 	//third insert 使用数组方式插入数据
// 	myfirst['w']=60; 
	//fourth insert 在iterator位置上插入pair数据
	multimap<char,int>::iterator ite=myfirst.begin();
	myfirst.insert(ite,pair<char,int>('b',300));  
	//比map插入数据方式少了：使用数组方式插入数据
	cout<<"myfirst\n";
	for (multimap<char,int>::iterator iter=myfirst.begin();iter!=myfirst.end();iter++)
	{
		cout<<iter->first<<"=>"<<iter->second<<endl;
		//a=>100
		//b=>300
		//f=>50
		//f=>60
	} 

	multimap<int,int> mymap;
	mymap.insert(multimap<int,int>::value_type(3,30));
	mymap.insert(multimap<int,int>::value_type(3,100)); 
	mymap.clear();//全部删除
	mymap.insert(multimap<int,int>::value_type(3,30));
	mymap.insert(multimap<int,int>::value_type(3,100));
	while(!mymap.empty())
	{
		cout<<mymap.begin()->first<<"=>"<<mymap.begin()->second<<endl;
		//3=>30
		//3=>100
		mymap.erase(mymap.begin());//删除iterator
	}

	multimap<char,int> first;
	multimap<char,int>::iterator it;
	first.insert(pair<char,int>('a',12));
	first.insert(pair<char,int>('c',100));
	first.insert(pair<char,int>('d',12));
	first.insert(pair<char,int>('a',120));
	first.insert(pair<char,int>('f',123));
	first.insert(pair<char,int>('f',18));
	first.insert(pair<char,int>('a',169)); 

	it=first.find('a');//找到第一个关键字a时就返回
 	first.erase(it); //用iterator删除，it必须存在，
 	first.erase('f');//用关键字删除，删除其所有的关键字
 	it=first.find('d');
 	first.erase(it,first.end());//成片删除
	cout<<"--------------erase-------------\n";
	for (it=first.begin();it!=first.end();it++)
	{
		cout<<it->first<<"=>"<<it->second<<endl;
		//a=>120
		//a=>169
		//c=>100
	}	

	//与map不同的是：添加方面：multimap少了使用数组添加数据对的方式
	//                          删除方面：multimap使用关键子删除时，其删除的是其所有的相同的关键字
}
//访问获取元素；返回值是Type T
void test2()
{  
	//map，multimap都是通过iterator的first，second属性来访问其数据
	multimap<char,int> first; 
	first.insert(multimap<char,int>::value_type('a',30));
	first.insert(multimap<char,int>::value_type('c',100));
  
	cout<<"a=>"<<first.begin()->second<<endl;//a=>30
	cout<<"c=>"<<first.find('c')->second<<endl;//c=>100
	//cout<<"w=>"<<first.find('w')->second<<endl;//当关键字不存在时，运行出现错误

	multimap<int,int> a;
	a.insert(pair<int,int>(1,11));
	a.insert(pair<int,int>(2,12));
	a.insert(pair<int,int>(3,13));
	a.insert(pair<int,int>(3,21));
	a.insert(pair<int,int>(2,22));
	a.insert(pair<int,int>(1,31));
	a.insert(pair<int,int>(4,32));

	cout<<"begin-----按关键字已经排好序了"<<endl;
	for (multimap<int,int>::iterator it=a.begin();it!=a.end();it++)
	{
		cout<<it->first<<"=>"<<it->second<<endl;
		//1=>11
		//1=>31
		//2=>12
		//2=>22
		//3=>13
		//3=>21
		//4=>32
	}
	
	multimap<int,int>::iterator p_map;
	pair<multimap<int,int>::iterator, multimap<int,int>::iterator> ret;
	cout<<"输出相同的数据---"<<endl;
	for(p_map = a.begin() ; p_map != a.end();)
	{
		cout<<p_map->first<<" =>";
		ret = a.equal_range(p_map->first);
		for(p_map = ret.first; p_map != ret.second; ++p_map)
			cout<<" "<< (*p_map).second;
		cout<<endl;
		//1 => 11 31
		//2 => 12 22
		//3 => 13 21
		//4 => 32
	}
	//map，multimap都是通过iterator的first，second属性来访问其数据
}
//返回迭代器；返回值是iterator，或reverse_iterator
void test3()
{ 
	multimap<char,int> mymap;
	mymap.insert(pair<char,int>('b',100));
	mymap.insert(pair<char,int>('a',200));
	mymap.insert(pair<char,int>('c',500)); 
	mymap.insert(pair<char,int>('b',500)); 
	multimap<char,int>::iterator iter=mymap.begin();
	for (;iter!=mymap.end();iter++)
	{
		cout<<iter->first<<"=>"<<iter->second<<endl;
		//a=>200
		//b=>100
		//b=>500
		//c=>500
	}	 
	cout<<"----reverse_iterator----"<<endl;
	multimap<char,int>::reverse_iterator riter=mymap.rbegin();
	for (;riter!=mymap.rend();++riter)
	{ 
		cout<<riter->first<<"=>"<<riter->second<<endl;
		//c=>500
		//b=>500
		//b=>100
		//a=>200
	}
	//与map完全相同
} 
//其他
void test4()
{  
	multimap<char,int>mymap,second;
	mymap.insert(pair<char,int>('a',101));
	mymap.insert(pair<char,int>('b',202));
	mymap.insert(pair<char,int>('c',303));
	mymap.insert(pair<char,int>('d',404));
	mymap.insert(pair<char,int>('a',123)); 
	for (char c='a';c<'h';c++)
	{
		cout<<c;
		if (mymap.count(c)>0)
		{
			cout<<" is an element of mymap.\n";//a,b,c,d
		}
		else
			cout<<" is not an element of mymap.\n";//d,e,f,g		
	}
	cout<<"mymap.size() is "<<mymap.size()<<endl;//5

	second.insert(pair<char,int>('x',11));
	second.insert(pair<char,int>('y',22));
	second.insert(pair<char,int>('z',33)); 
	second.insert(pair<char,int>('y',321)); 

	second.swap(mymap);

	cout<<"mymap-----\n";
	for (multimap<char,int>::iterator it=mymap.begin();it!=mymap.end();it++)
	{
		cout<<it->first<<"=>"<<it->second<<endl;
		//x=>11
		//y=>22
		//y=>321
		//z=>33
	}
	cout<<"second-----\n";
	for (multimap<char,int>::iterator it=second.begin();it!=second.end();it++)
	{
		cout<<it->first<<"=>"<<it->second<<endl;
		//a=>101
		//a=>123
		//b=>202
		//c=>303
		//d=>404
	}
	//equal_range()：返回pair(iterator,iterator),pair中的第一个迭代器是lower_bound()返回的迭代器，pair中的第二个迭代器是upper_bound()返回的迭代器，如果两个迭代器相等，则说明map中不存在这个关键字
	pair<multimap<char,int>::iterator,multimap<char,int>::iterator> ret=mymap.equal_range('y');
	cout<<"lower bound points to: "<<ret.first->first<<"=>"<<ret.first->second<<endl;//y=>22，当关键字y不存在时，则输出begin()->first,begin()->second;还有就是ret.second->first不存在！！！
	cout<<"upper bound points to: "<<ret.second->first<<"=>"<<ret.second->second<<endl;//z=>33,必须确保关键字y后面有别的不同于y的关键字

	multimap<char,int>::iterator itlow,itup;
	//lower_bound():返回是iterator，返回要查找关键字的下界(是一个迭代器)
	//upper_bound():返回是iterator，返回要查找关键字的上界(是一个迭代器)
	itlow=second.lower_bound('b');//itlow points to b
	itup=second.upper_bound('c');//itup points to d (not c)
	second.erase(itlow,itup);//删除[itlow,itup)
	cout<<"itlow+++++++itup\n";
	for (multimap<char,int>::iterator it=second.begin();it!=second.end();it++)
	{
		cout<<it->first<<"=>"<<it->second<<endl; 
		//a=>101
		//a=>123
		//d=>404
	}
	second.insert(pair<char,int>('p',505));
	multimap<char,int>::key_compare mycomp=second.key_comp();
	char highest=second.rbegin()->first;
	multimap<char,int>::iterator item=second.begin();
	cout<<"key_compare\n";
	do 
	{
		cout<<item->first<<"=>"<<item->second<<endl; 
		//a=>101
		//a=>123 
		//d=>404
		//p=>505
	}while(mycomp((*item++).first,highest));

	cout<<"value_compare\n";
	pair<char,int> high=*second.rbegin();
	multimap<char,int>::iterator io=second.begin();
	do 
	{
		cout<<io->first<<"=>"<<io->second<<endl; 
		//a=>101
		//a=>123 
		//d=>404
		//p=>505
	} while (second.value_comp()(*io++,high));
	//其所有函数的功能即用法都有map相同
} 
//遍历map中的数据
void test5()
{  
	//1.使用前向迭代器
	//2.使用相反迭代器
	//------没有了3.使用数组(不完全正确，当数据插入时键值完全顺序才正确，不然会出现二叉树的输出结果)
	multimap<int,int> mymap;
	mymap.insert(multimap<int,int>::value_type(3,30));
	mymap.insert(multimap<int,int>::value_type(3,100));
	mymap.insert(multimap<int,int>::value_type(5,50)); 
	mymap.insert(multimap<int,int>::value_type(1,10));  
	multimap<int,int>::iterator iter=mymap.begin();
	for (;iter!=mymap.end();iter++)
	{
		cout<<iter->first<<"=>"<<iter->second<<endl;
		//1=>10
		//3=>30
		//3=>100
		//5=>50
	}	 
	cout<<"----reverse_iterator----"<<endl;
	multimap<int,int>::reverse_iterator riter=mymap.rbegin();
	for (;riter!=mymap.rend();++riter)
	{ 
		cout<<riter->first<<"=>"<<riter->second<<endl;
		//5=>50
		//3=>100
		//3=>30
		//0=>10
	}
	cout<<"mymap size:"<<mymap.size()<<endl;//4
    //与map相比：少了数组遍历
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