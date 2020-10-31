//����������ͨ�� �� �洢�Ͷ�ȡԪ�ء�˳��������ͨ��Ԫ���������е�λ��˳��洢�Ͷ�ȡԪ�ء�
//����������˳�������ı��ʲ�����ڣ���������ͨ������key���洢�Ͷ�ȡԪ�أ���˳��������ͨ��Ԫ���������е�λ��˳��洢�ͷ���Ԫ�ء�
/*
map�Ǳ�׼����ʽ����֮һ��һ��map��һ����ֵ�����У���(key��value)�ԡ����ṩ�˻���key�Ŀ��ټ�����������һ��map��keyֵ��Ψһ�ġ�map�ṩ��˫�������������ǰ�����(iterator)��Ҳ�дӺ���ǰ��(reverse_iterator)��
mapҪ���ܶ�key���в������ұ��ְ�keyֵ�����������map�ϵĵ�����Ҳ�ǵ�������ġ��������Ԫ�ز�����Ҫ�������򣬿���ʹ��hash_map��
map��keyֵ��Ψһ�ģ����map���Ѵ���һ����ֵ��(�ǳƣ�����):("sky",789852)�������ǻ��������һ����ֵ��("sky",789852)��ᱨ��(���Ǳ���׼ȷ��˵�ǣ����ز��벻�ɹ���)���������е�ȷ������������һ�������ڶ��ֵ�����˵���multimap����ʵ��������ܡ�

map��һ����������������ص������Ӻ�ɾ���ڵ�Ե�������Ӱ���С�������Ǹ������ڵ㣬�������ڵ㶼û��ʲôӰ�졣��Ϊ���ڲ��ṹʽ��ڶ����������ڵ�������˵�����޸�ʵֵvalue���������޸Ĺؼ���key��
map�Ĺ���
�Զ�����key-value�Ķ�Ӧ��key��value����ʹ��������Ҫ�����͡�
����keyֵ���ٲ��Ҽ�¼�����ҵĸ��ӶȻ�����log(N)
���ٲ���key-value��¼
����ɾ����¼
����key�޸�value��¼
�������м�¼
*/
/*
#include <string>
#include <map>  
#include <conio.h>
#include<iostream>
using namespace std;   
//���弰��ʼ����û�з���ֵ����void
void test0()
{  
	multimap<int,string> first;
	first.insert(pair<int,string>(3,"hello"));
	multimap<int,string> second(first);//�������캯��
	multimap<int,string> third(first.begin(),first.end());//���乹�캯��
}
//����ɾ��Ԫ�أ�����ֵ��void,��erase()�ķ���ֵ��iterator��
void test1()
{ 	 
	//first insert ��insert()��������pair����
	multimap<char,int> myfirst;
	myfirst.insert(pair<char,int>('a',100)); 
	//second insert ��insert()��������value_type����
	myfirst.insert(map<char,int>::value_type('f',50)); //������map<char,int>Ҳ������multimap<char,int>
	myfirst.insert(map<char,int>::value_type('f',60));  
// 	//third insert ʹ�����鷽ʽ��������
// 	myfirst['w']=60; 
	//fourth insert ��iteratorλ���ϲ���pair����
	multimap<char,int>::iterator ite=myfirst.begin();
	myfirst.insert(ite,pair<char,int>('b',300));  
	//��map�������ݷ�ʽ���ˣ�ʹ�����鷽ʽ��������
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
	mymap.clear();//ȫ��ɾ��
	mymap.insert(multimap<int,int>::value_type(3,30));
	mymap.insert(multimap<int,int>::value_type(3,100));
	while(!mymap.empty())
	{
		cout<<mymap.begin()->first<<"=>"<<mymap.begin()->second<<endl;
		//3=>30
		//3=>100
		mymap.erase(mymap.begin());//ɾ��iterator
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

	it=first.find('a');//�ҵ���һ���ؼ���aʱ�ͷ���
 	first.erase(it); //��iteratorɾ����it������ڣ�
 	first.erase('f');//�ùؼ���ɾ����ɾ�������еĹؼ���
 	it=first.find('d');
 	first.erase(it,first.end());//��Ƭɾ��
	cout<<"--------------erase-------------\n";
	for (it=first.begin();it!=first.end();it++)
	{
		cout<<it->first<<"=>"<<it->second<<endl;
		//a=>120
		//a=>169
		//c=>100
	}	

	//��map��ͬ���ǣ���ӷ��棺multimap����ʹ������������ݶԵķ�ʽ
	//                          ɾ�����棺multimapʹ�ùؼ���ɾ��ʱ����ɾ�����������е���ͬ�Ĺؼ���
}
//���ʻ�ȡԪ�أ�����ֵ��Type T
void test2()
{  
	//map��multimap����ͨ��iterator��first��second����������������
	multimap<char,int> first; 
	first.insert(multimap<char,int>::value_type('a',30));
	first.insert(multimap<char,int>::value_type('c',100));
  
	cout<<"a=>"<<first.begin()->second<<endl;//a=>30
	cout<<"c=>"<<first.find('c')->second<<endl;//c=>100
	//cout<<"w=>"<<first.find('w')->second<<endl;//���ؼ��ֲ�����ʱ�����г��ִ���

	multimap<int,int> a;
	a.insert(pair<int,int>(1,11));
	a.insert(pair<int,int>(2,12));
	a.insert(pair<int,int>(3,13));
	a.insert(pair<int,int>(3,21));
	a.insert(pair<int,int>(2,22));
	a.insert(pair<int,int>(1,31));
	a.insert(pair<int,int>(4,32));

	cout<<"begin-----���ؼ����Ѿ��ź�����"<<endl;
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
	cout<<"�����ͬ������---"<<endl;
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
	//map��multimap����ͨ��iterator��first��second����������������
}
//���ص�����������ֵ��iterator����reverse_iterator
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
	//��map��ȫ��ͬ
} 
//����
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
	//equal_range()������pair(iterator,iterator),pair�еĵ�һ����������lower_bound()���صĵ�������pair�еĵڶ�����������upper_bound()���صĵ����������������������ȣ���˵��map�в���������ؼ���
	pair<multimap<char,int>::iterator,multimap<char,int>::iterator> ret=mymap.equal_range('y');
	cout<<"lower bound points to: "<<ret.first->first<<"=>"<<ret.first->second<<endl;//y=>22�����ؼ���y������ʱ�������begin()->first,begin()->second;���о���ret.second->first�����ڣ�����
	cout<<"upper bound points to: "<<ret.second->first<<"=>"<<ret.second->second<<endl;//z=>33,����ȷ���ؼ���y�����б�Ĳ�ͬ��y�Ĺؼ���

	multimap<char,int>::iterator itlow,itup;
	//lower_bound():������iterator������Ҫ���ҹؼ��ֵ��½�(��һ��������)
	//upper_bound():������iterator������Ҫ���ҹؼ��ֵ��Ͻ�(��һ��������)
	itlow=second.lower_bound('b');//itlow points to b
	itup=second.upper_bound('c');//itup points to d (not c)
	second.erase(itlow,itup);//ɾ��[itlow,itup)
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
	//�����к����Ĺ��ܼ��÷�����map��ͬ
} 
//����map�е�����
void test5()
{  
	//1.ʹ��ǰ�������
	//2.ʹ���෴������
	//------û����3.ʹ������(����ȫ��ȷ�������ݲ���ʱ��ֵ��ȫ˳�����ȷ����Ȼ����ֶ�������������)
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
    //��map��ȣ������������
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