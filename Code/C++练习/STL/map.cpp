// ����������ͨ�� �� �洢�Ͷ�ȡԪ�ء�˳��������ͨ��Ԫ���������е�λ��˳��洢�Ͷ�ȡԪ�ء�
// ����������˳�������ı��ʲ�����ڣ���������ͨ������key���洢�Ͷ�ȡԪ�أ���˳��������ͨ��Ԫ���������е�λ��˳��洢�ͷ���Ԫ�ء�
// /*
// map�Ǳ�׼����ʽ����֮һ��һ��map��һ����ֵ�����У���(key��value)�ԡ����ṩ�˻���key�Ŀ��ټ�����������һ��map��keyֵ��Ψһ�ġ�map�ṩ��˫�������������ǰ�����(iterator)��Ҳ�дӺ���ǰ��(reverse_iterator)��
// mapҪ���ܶ�key���в������ұ��ְ�keyֵ�����������map�ϵĵ�����Ҳ�ǵ�������ġ��������Ԫ�ز�����Ҫ�������򣬿���ʹ��hash_map��
// map��keyֵ��Ψһ�ģ����map���Ѵ���һ����ֵ��(�ǳƣ�����):("sky",789852)�������ǻ��������һ����ֵ��("sky",789852)��ᱨ��(���Ǳ���׼ȷ��˵�ǣ����ز��벻�ɹ���)���������е�ȷ������������һ�������ڶ��ֵ�����˵���multimap����ʵ��������ܡ�
// 
// map��һ����������������ص������Ӻ�ɾ���ڵ�Ե�������Ӱ���С�������Ǹ������ڵ㣬�������ڵ㶼û��ʲôӰ�졣��Ϊ���ڲ��ṹʽ��ڶ����������ڵ�������˵�����޸�ʵֵvalue���������޸Ĺؼ���key��
// map�Ĺ���
// �Զ�����key-value�Ķ�Ӧ��key��value����ʹ��������Ҫ�����͡�
// ����keyֵ���ٲ��Ҽ�¼�����ҵĸ��ӶȻ�����log(N)
// ���ٲ���key-value��¼
// ����ɾ����¼
// ����key�޸�value��¼
// �������м�¼
// */
// #include <string>
// #include <map>  
// #include <conio.h>
// #include<iostream>
// using namespace std;   
// ���弰��ʼ����û�з���ֵ����void
// void test0()
// {  
// 	map<int,string> first;
// 	first.insert(pair<int,string>(3,"hello"));
// 	map<int,string> second(first);//�������캯��
// 	map<int,string> third(first.begin(),first.end());//���乹�캯��
// }
// ����ɾ��Ԫ�أ�����ֵ��void,��erase()�ķ���ֵ��iterator��
// void test1()
// { 	 
// 	//first insert ��insert()��������pair����
// 	map<char,int> myfirst;
// 	myfirst.insert(pair<char,int>('a',100)); 
// 	//second insert ��insert()��������value_type����
// 	myfirst.insert(map<char,int>::value_type('f',50)); 
// 	//third insert ʹ�����鷽ʽ��������
// 	myfirst['w']=60; 
// 	//fourth insert ��iteratorλ���ϲ���pair����
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
// 	first.erase(it); //�õ�����ɾ��
// 	first.erase('c');//�ùؼ���ɾ��
// 	it=first.find('e');
// 	first.erase(it,first.end());//��Ƭɾ��
// 	cout<<"--------------erase-------------\n";
// 	for (it=first.begin();it!=first.end();it++)
// 	{
// 		cout<<it->first<<"=>"<<it->second<<endl;
// 		//a=>10
// 		//b=>40
// 	}	
// }
// ���ʻ�ȡԪ�أ�����ֵ��Type T
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
// 	//cout<<"w=>"<<first.find('w')->second<<endl;//���ؼ��ֲ�����ʱ�����г��ִ���
// 	 
// }
// ���ص�����������ֵ��iterator����reverse_iterator
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
// ����
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
// 	//equal_range()������pair(iterator,iterator),pair�еĵ�һ����������lower_bound()���صĵ�������pair�еĵڶ�����������upper_bound()���صĵ����������������������ȣ���˵��map�в���������ؼ���
// 	pair<map<char,int>::iterator,map<char,int>::iterator> ret=mymap.equal_range('y');
// 	cout<<"lower bound points to: "<<ret.first->first<<"=>"<<ret.first->second<<endl;//y=>22
// 	cout<<"upper bound points to: "<<ret.second->first<<"=>"<<ret.second->second<<endl;//z=>33
// 
// 	map<char,int>::iterator itlow,itup;
// 	//lower_bound():������iterator������Ҫ���ҹؼ��ֵ��½�(��һ��������)
// 	//upper_bound():������iterator������Ҫ���ҹؼ��ֵ��Ͻ�(��һ��������)
// 	itlow=second.lower_bound('b');//itlow points to b
// 	itup=second.upper_bound('c');//itup points to d (not c)
// 	second.erase(itlow,itup);//ɾ��[itlow,itup)
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
// ����map�е�����
// void test5()
// {  
// 	//1.ʹ��ǰ�������
// 	//2.ʹ���෴������
// 	//3.ʹ������(����ȫ��ȷ�������ݲ���ʱ��ֵ��ȫ˳�����ȷ����Ȼ����ֶ�������������)
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
// 		//map���������ڲ������ɺ������֤����˺ܶຯ��ִ�е�ʱ�临�Ӷȶ���log2N
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
