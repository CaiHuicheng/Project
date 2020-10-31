// 关联容器，通过 键 存储和读取元素。顺序容器，通过元素在容器中的位置顺序存储和读取元素。
// 关联容器和顺序容器的本质差别在于：关联容器通过键（key）存储和读取元素，而顺序容器则通过元素在容器中的位置顺序存储和访问元素。
// /*
// map是标准关联式容器之一，一个map是一个键值对序列，即(key，value)对。它提供了基于key的快速检索能力，在一个map中key值是唯一的。map提供了双向迭代器，即从前往后的(iterator)，也有从后往前的(reverse_iterator)。
// map要求能对key进行操作，且保持按key值递增有序，因此map上的迭代器也是递增有序的。如果对于元素并不需要保持有序，可以使用hash_map。
// map中key值是唯一的，如果map中已存在一个键值对(昵称，密码):("sky",789852)，而我们还是想插入一个键值对("sky",789852)则会报错(不是报错，准确的说是，返回插入不成功！)。而我们有的确想这样做，即一个键对于多个值，幸运的是multimap可以实现这个功能。
// 
// map是一类关联容器。它的特点是增加和删除节点对迭代器的影响很小，除了那个操作节点，对其他节点都没有什么影响。因为它内部结构式红黑二叉树。对于迭代器来说可以修改实值value，而不能修改关键字key。
// map的功能
// 自动建立key-value的对应。key和value可以使任意你需要的类型。
// 根据key值快速查找记录，查找的复杂度基本是log(N)
// 快速插入key-value记录
// 快速删除记录
// 根据key修改value记录
// 遍历所有记录
// */
// #include <string>
// #include <map>  
// #include <conio.h>
// #include<iostream>
// using namespace std;   
// 定义及初始化；没有返回值，或void
// void test0()
// {  
// 	map<int,string> first;
// 	first.insert(pair<int,string>(3,"hello"));
// 	map<int,string> second(first);//拷贝构造函数
// 	map<int,string> third(first.begin(),first.end());//区间构造函数
// }
// 增加删除元素；返回值是void,除erase()的返回值是iterator外
// void test1()
// { 	 
// 	//first insert 用insert()函数插入pair数据
// 	map<char,int> myfirst;
// 	myfirst.insert(pair<char,int>('a',100)); 
// 	//second insert 用insert()函数插入value_type数据
// 	myfirst.insert(map<char,int>::value_type('f',50)); 
// 	//third insert 使用数组方式插入数据
// 	myfirst['w']=60; 
// 	//fourth insert 在iterator位置上插入pair数据
// 	map<char,int>::iterator ite=myfirst.begin();
// 	myfirst.insert(ite,pair<char,int>('b',300));  
// 	 
// 	cout<<"myfirst\n";
// 	for (map<char,int>::iterator iter=myfirst.begin();iter!=myfirst.end();iter++)
// 	{
// 		cout<<iter->first<<"=>"<<iter->second<<endl;
// 		//a=>100
// 		//b=>300
// 		//f=>50
// 		//w=>60
// 	} 
// 	map<int,int>mymap;
// 	for (int i=0;i<3;i++)
// 	{
// 		mymap[i]=i*100;
// 	} 
// 	for (map<int,int>::iterator iter=mymap.begin();iter!=mymap.end();iter++)
// 	{
// 		cout<<iter->first<<"=>"<<iter->second<<endl;
// 		//0=>0
// 		//1=>100
// 		//2=>200
// 	}
// 	mymap.clear();
// 	mymap[8]=20;
// 	mymap[5]=60; 
// 	while(!mymap.empty())
// 	{
// 		cout<<mymap.begin()->first<<"=>"<<mymap.begin()->second<<endl;
// 		//5=>60
// 		//8=>20
// 		mymap.erase(mymap.begin());
// 	}
// 	map<char,int> first;
// 	map<char,int>::iterator it;
//     first['a']=10;
// 	first['b']=20;
// 	first['c']=30;
// 	first['d']=40;
// 	first['e']=50;
// 	first['f']=60;
// 	first['g']=70;
// 	first['h']=80;
// 	
// 	it=first.find('b');
// 	first.erase(it); //用迭代器删除
// 	first.erase('c');//用关键字删除
// 	it=first.find('e');
// 	first.erase(it,first.end());//成片删除
// 	cout<<"--------------erase-------------\n";
// 	for (it=first.begin();it!=first.end();it++)
// 	{
// 		cout<<it->first<<"=>"<<it->second<<endl;
// 		//a=>10
// 		//b=>40
// 	}	
// }
// 访问获取元素；返回值是Type T
// void test2()
// {  
// 	map<char,int> first;
// 	map<char,int>::iterator it;
// 	first['a']=10;
// 	first['b']=20;
// 	first['c']=30;
// 	first['d']=40;
// 	it=first.find('b');
// 	first.erase(it);
// 	first.erase(first.find('d'));
// 	cout<<"a=>"<<first.begin()->second<<endl;//a=>10
// 	cout<<"c=>"<<first.find('c')->second<<endl;//c=>30
// 	//cout<<"w=>"<<first.find('w')->second<<endl;//当关键字不存在时，运行出现错误
// 	 
// }
// 返回迭代器；返回值是iterator，或reverse_iterator
// void test3()
// { 
// 	map<char,int> mymap;
// 	mymap['b']=100;
// 	mymap['a']=200;
// 	mymap['c']=500;
// 	map<char,int>::iterator iter=mymap.begin();
// 	for (;iter!=mymap.end();iter++)
// 	{
// 		cout<<iter->first<<"=>"<<iter->second<<endl;
// 		//a=>200
// 		//b=>100
// 		//c=>500
// 	}	 
// 	cout<<"----reverse_iterator----"<<endl;
// 	map<char,int>::reverse_iterator riter=mymap.rbegin();
// 	for (;riter!=mymap.rend();++riter)
// 	{ 
// 		cout<<riter->first<<"=>"<<riter->second<<endl;
// 		//c=>500
// 		//b=>100
// 		//a=>200
// 	}
// 	
// } 
// 其他
// void test4()
// {  
// 	map<char,int>mymap,second;
// 	mymap['a']=101;
// 	mymap['b']=202;
// 	mymap['c']=303;
// 	mymap['d']=404;
// 	for (char c='a';c<'h';c++)
// 	{
// 		cout<<c;
// 		if (mymap.count(c)>0)
// 		{
// 			cout<<" is an element of mymap.\n";//a,b,c,d
// 		}
// 		else
// 			cout<<" is not an element of mymap.\n";//d,e,f,g		
// 	}
// 	cout<<"mymap.size() is "<<mymap.size()<<endl;//3
// 
// 	second['x']=11;
// 	second['y']=22;
// 	second['z']=33;
// 	second.swap(mymap);
// 
// 	cout<<"mymap-----\n";
// 	for (map<char,int>::iterator it=mymap.begin();it!=mymap.end();it++)
// 	{
// 		cout<<it->first<<"=>"<<it->second<<endl;
// 		//x=>11
// 		//y=>22
// 		//z=>33
// 	}
// 	cout<<"second-----\n";
// 	for (map<char,int>::iterator it=second.begin();it!=second.end();it++)
// 	{
// 		cout<<it->first<<"=>"<<it->second<<endl;
// 		//a=>101
// 		//b=>202
// 		//c=>303
// 		//d=>404
// 	}
// 	//equal_range()：返回pair(iterator,iterator),pair中的第一个迭代器是lower_bound()返回的迭代器，pair中的第二个迭代器是upper_bound()返回的迭代器，如果两个迭代器相等，则说明map中不存在这个关键字
// 	pair<map<char,int>::iterator,map<char,int>::iterator> ret=mymap.equal_range('y');
// 	cout<<"lower bound points to: "<<ret.first->first<<"=>"<<ret.first->second<<endl;//y=>22
// 	cout<<"upper bound points to: "<<ret.second->first<<"=>"<<ret.second->second<<endl;//z=>33
// 
// 	map<char,int>::iterator itlow,itup;
// 	//lower_bound():返回是iterator，返回要查找关键字的下界(是一个迭代器)
// 	//upper_bound():返回是iterator，返回要查找关键字的上界(是一个迭代器)
// 	itlow=second.lower_bound('b');//itlow points to b
// 	itup=second.upper_bound('c');//itup points to d (not c)
// 	second.erase(itlow,itup);//删除[itlow,itup)
// 	cout<<"itlow,itup\n";
// 	for (map<char,int>::iterator it=second.begin();it!=second.end();it++)
// 	{
// 		cout<<it->first<<"=>"<<it->second<<endl; 
// 		//a=>101
// 		//d=>404
// 	}
// 	second['p']=505;
// 	map<char,int>::key_compare mycomp=second.key_comp();
// 	char highest=second.rbegin()->first;
// 	map<char,int>::iterator item=second.begin();
// 	cout<<"key_compare\n";
// 	do 
// 	{
// 		cout<<item->first<<"=>"<<item->second<<endl; 
// 	}while(mycomp((*item++).first,highest));
// 
// 	cout<<"value_compare\n";
// 	pair<char,int> high=*second.rbegin();
// 	map<char,int>::iterator io=second.begin();
// 	do 
// 	{
// 		cout<<io->first<<"=>"<<io->second<<endl; 
// 	} while (second.value_comp()(*io++,high));
// 	
// } 
// 遍历map中的数据
// void test5()
// {  
// 	//1.使用前向迭代器
// 	//2.使用相反迭代器
// 	//3.使用数组(不完全正确，当数据插入时键值完全顺序才正确，不然会出现二叉树的输出结果)
// 	map<int,int> mymap;
// 	mymap[0]=100;
// 	mymap[3]=200;
// 	mymap[2]=500;
// 	map<int,int>::iterator iter=mymap.begin();
// 	for (;iter!=mymap.end();iter++)
// 	{
// 		cout<<iter->first<<"=>"<<iter->second<<endl;
// 		//0=>100
// 		//2=>500
// 		//3=>200
// 	}	 
// 	cout<<"----reverse_iterator----"<<endl;
// 	map<int,int>::reverse_iterator riter=mymap.rbegin();
// 	for (;riter!=mymap.rend();++riter)
// 	{ 
// 		cout<<riter->first<<"=>"<<riter->second<<endl;
// 		//3=>200
// 		//2=>500
// 		//0=>100
// 	}
// 	cout<<"mymap size:"<<mymap.size()<<endl;
// 	for (int i=0;i<mymap.size();i++)
// 	{
// 		cout<<mymap[i]<<endl;
// 		//100
// 		//0
// 		//500 
// 		//200
// 		//map中由于他内部有序，由红黑树保证，因此很多函数执行的时间复杂度都是log2N
// 	}	
// } 
// void Test(char h)
// {
// 	cout<<"press key===="<<h<<endl;
// 	switch(h)
// 	{ 
// 	case '0':  test0();break;
// 	case '1':  test1();break;
// 	case '2':  test2();break;
// 	case '3':  test3();break;
// 	case '4':  test4();break;
// 	case '5':  test5();break; 
// 	case 27:
// 	case 'q':exit(0);break; 
// 	default:cout<<"default "<<h<<endl;break;
// 	}
// }
// void main()
// {
// 	while(1)
// 	{
// 		Test(getch());
// 	} 
// }
