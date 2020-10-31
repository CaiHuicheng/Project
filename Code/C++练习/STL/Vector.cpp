/*
#include <string>
#include <vector> 
#include <conio.h>
#include<iostream>
using namespace std;  
//���弰��ʼ��������void���޷���ֵ
void test0()
{ 
	vector<int> v;//ֻ������v��û�з����ڴ�ռ�
	vector<int> ve(2);//���岢������2int�ռ��ve��ȱʡΪ0
	vector<int> vec(3,4);//���岢��ʼ����3��4��vec
	cout<<v.size()<<" "<<ve.size()<<" "<<vec.size()<<endl;//0 2 3
	cout<<"ve:"<<ve[0]<<" "<<ve[1]<<endl;//ve: 0 0
	cout<<"vec:"<<vec[0]<<" "<<vec[1]<<" "<<vec[2]<<endl;//vec: 4 4 4
	v.assign(3,8);//��ֵ3��8
	ve.assign(vec.begin(),vec.end());//��ֵ3��4
	for (int i=0;i<v.size();i++) 
		cout<<v[i]<<" "; //8 8 8 
	cout<<endl;
	for (int i=0;i<ve.size();i++) 
		cout<<ve[i]<<" ";//4 4 4 
	cout<<endl;
	ve.assign(0,0);//��ֵ0��0���ҿ��Կ��������ڴ��Ǳ仯��.��Ϊ��
	for (int i=0;i<ve.size();i++) 
		cout<<ve[i]<<" ";//Ϊ�� 
	cout<<endl;    
}
//����ɾ��Ԫ�أ�����void����erase()����iterator��
void test1()
{ 
	vector<char> v(2,'A');
	v.push_back('B');//��β������һ������
	cout<<v[0]<<" "<<v[1]<<' '<<v[2]<<endl;//A A B
	v.pop_back();//ɾ�����һ������
	v.insert(v.begin()+1,'C');//�ڵڶ���λ���ϲ�����'C'
	v.insert(v.begin(),2,'D'); //�ڵ�һ���ڶ���λ���Ϸֱ����'C'
	v.insert(v.end(),v.begin(),v.end());//����ĩ�˲�������֮ǰ������Ԫ�أ����ڸ�����
	for (int i=0;i<v.size();i++) 
		cout<<v[i]<<" "; //D D A C A D D A C A
	cout<<endl;

	v.erase(v.begin());//ɾ����һ��Ԫ��
	for (int i=0;i<v.size();i++) 
		cout<<v[i]<<" "; //D A C A D D A C A
	cout<<endl;
	v.erase(v.begin()+1,v.end()-1);//�������˵�Ԫ�أ�ɾ���м��Ԫ��
	for (int i=0;i<v.size();i++) 
		cout<<v[i]<<" "; //D A
	cout<<endl;
	v.clear();//ɾ��ȫ��
	for (int i=0;i<v.size();i++) 
		cout<<v[i]<<" "; //Ϊ��
	cout<<endl;
}
//���ʻ�ȡԪ�أ�����TYPE &T
void test2()
{ 
	string str[]={"one","two","three","four","five","six"};
	vector<string> ve;
	for(int i=0;i<6;i++) 
	{
		ve.push_back(str[i]); 
		cout<<ve[i]<<" ";//ͨ������ֵi�����з���,ʹ�õ����������ʽ����Ȼ����Խ��
	}
	cout<<endl;
	for(int i=0;i<6;i++) 
	{ 
		cout<<ve.at(i)<<" ";//ʹ��at()ͨ��i�����з��ʣ�Ҳ����Խ�硣��Խ�磬�ڵ���ʱ�����׳��쳣��������ʱֱ�ӵ�������
	}
	cout<<endl;
	cout<<ve.front()<<endl;//one //���ص�һ��Ԫ�ص�����
	cout<<ve.back()<<endl;//six //�������һ��Ԫ�ص����� 
}
//������������iterator����reverse_iterator
void test3()
{ 
	vector<int>ve(4);
	ve[0]=0;ve[1]=1;ve[2]=2;ve[3]=3;
	cout<<ve[0]<<" "<<ve[1]<<" "<<ve[2]<<" "<<ve[3]<<endl;
	vector<int>::iterator iter;//����һ��������iter
	iter=ve.begin();//����һ��iterator����ָ��vector��һ��Ԫ��
	cout<<*iter<<endl;//0
	iter=ve.end();//����һ��iterator����ָ��vector��ĩβԪ�ص���һ��λ��(������ĩβԪ��)
	//cout<<*iter<<endl;//����ִ���
	cout<<*(iter-1)<<endl;//3 �ô˷�������ĩβԪ��
	vector<int>::reverse_iterator reIter;//����һ������ĵ�����
	reIter=ve.rbegin();//����һ������iterator����ָ��vectorĩβԪ��
	cout<<*reIter<<endl;//3
	reIter=ve.rend();//����һ������iterator����ָ��vector��һ��Ԫ��֮ǰ��λ��(���ǲ����ڵ�)
	cout<<*(reIter-1)<<endl;//0  �ô˷������ʵ�һ��Ԫ��
} 
//ȡ�á����ó��ȡ�����������void��size_type
void test4()
{ 
	vector<string> ve(8);
	cout<<ve.size()<<endl;//8
	cout<<ve.max_size()<<endl;//134217727��10737441823
	cout<<ve.capacity()<<endl;//8
	cout<<ve.empty()<<endl;//0,˵����Ϊ�գ���ΪĬ��ֵ��0

	ve.assign(12,"3");
	cout<<ve.size()<<endl;//12
	cout<<ve.max_size()<<endl;//134217727(string),10737441823(int)
	cout<<ve.capacity()<<endl;//12
	cout<<ve.empty()<<endl;//0 

	ve.assign(1,"003");
	cout<<ve.size()<<endl;//1  ����vector��ǰ����Ԫ�صĸ���
	cout<<ve.max_size()<<endl;//���������������������й�
	cout<<ve.capacity()<<endl;//12 ���� ȡ��vectorĿǰ�����ɵ����Ԫ�ظ��������������洢�����йأ���ͨ��ֻ�����ӣ�������ΪԪ�ر�ɾ������֮����
	cout<<ve.empty()<<endl;//0 Ϊ��ʱ������true

	ve.resize(15,"W");//�ı�vectorĿǰ����Ԫ�صĸ���
	cout<<ve.size()<<endl;//15
	cout<<ve.max_size()<<endl;//134217727(string),10737441823(int)
	cout<<ve.capacity()<<endl;//18
	cout<<ve.empty()<<endl;//0 

	ve.reserve(5);//���б�Ҫ���ɸı�vector��������С(ֻ�����ӣ����ٲ�������)
	cout<<ve.size()<<endl;//15
	cout<<ve.max_size()<<endl;//134217727(string),10737441823(int)
	cout<<ve.capacity()<<endl;//18 ��ve.reserve(35);�����35����˵������capacityֻ�����Ӳ������
	cout<<ve.empty()<<endl;//0 

	vector<int> v(2,4);
	vector<int>vec(5,9);
	vec.swap(v);//����vector���н���
	cout<<v.size()<<" "<<v[0]<<endl;//5 9
	cout<<vec.size()<<" "<<vec[0]<<endl;//2 4
	//����size��ָ������ǰӵ��Ԫ�صĸ���

} 
//����vector
void test5()
{ 
	vector<int> vec;
	for (int i=0;i<10;i++)
	{
		vec.push_back(i);
	}
	for (int i=0;i<vec.size();i++) 
		cout<<vec[i]<<" ";
	cout<<endl;

	vector<int>::iterator iter;
	for (iter=vec.begin();iter!=vec.end();iter++)
		cout<<*iter<<" ";
	cout<<endl;

	vector<int>::reverse_iterator reIter;
	for (reIter=vec.rbegin();reIter!=vec.rend();reIter++) 
		cout<<*reIter<<" ";//9 8 7 6 5 4 3 2 1 0
	cout<<endl;

	vector<int>::reverse_iterator revIter;
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