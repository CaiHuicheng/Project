

#include <conio.h> 
#include <iostream>
#include <string>
using namespace std; 
//1.���캯��
/*
string();
string( size_type length, char ch );
string( const char *str );
string( const char *str, size_type index );
string( string &str, size_type index, size_type length );
string( input_iterator start, input_iterator end );
�ַ����Ĺ��캯������һ�����ַ���������: 
1.��lengthΪ���ȵ�ch�Ŀ�������length��ch�� 
2.��strΪ��ֵ (��������), 
3.��indexΪ������ʼ���Ӵ�������Ϊlength,���� 
4.�Դ�start��end��Ԫ��Ϊ��ֵ.
*/
void test0()
{   
	string str1(5,'c');
	string str2("Now is the time...");
	string str3(str2,5);
	string str4(str2,1,4);
	cout<<str1<<endl;//ccccc
	cout<<str2<<endl;//Now is the time...
	cout<<str3<<endl;//s the time...
	cout<<str4<<endl;//ow i
} 
//2.������
/*
1.��==, >, <, >=, <=, and !=�Ƚ��ַ���,compare()
2.�� + ���� += ���������������ַ���
3.��[]��ȡ�ض����ַ�-->at()
A.compare()
int compare( const basic_string &str );
int compare( const char *str );
int compare( size_type index, size_type length, const basic_string &str );
int compare( size_type index, size_type length, const basic_string &str, size_type index2,
size_type length2 );
int compare( size_type index, size_type length, const char *str, size_type length2 );
����ֵ ��� :С���� this < str ;�� this == str ;������ this > str 
��ͬ�ĺ���: 
1.�Ƚ��Լ���str, 
2.�Ƚ��Լ����Ӵ���str,�Ӵ���index������ʼ������Ϊlength 
3.�Ƚ��Լ����Ӵ���str���Ӵ�������index2��length2����str��index��length�����Լ� 
4.�Ƚ��Լ����Ӵ���str���Ӵ�������str���Ӵ�������0��ʼ������Ϊlength2���Լ����Ӵ���index��ʼ������Ϊlength 
*/
void test1()
{ 	 
	string str1("hello"); 
	cout<<str1[1]<<"  "<<str1.at(4)<<endl;//e o //ע���±겻Ҫ���磬��������
} 
//����ı� append();��ֵassign()
/*
basic_string &append( const basic_string &str );
basic_string &append( const char *str );
basic_string &append( const basic_string &str, size_type index, size_type len );
basic_string &append( const char *str, size_type num );
basic_string &append( size_type num, char ch );
append() ��������������¹���: 
1.���ַ�����ĩβ���str, 
2.���ַ�����ĩβ���str���Ӵ�,�Ӵ���index������ʼ������Ϊlen 
3.���ַ�����ĩβ���str�е�num���ַ�, 
4.���ַ�����ĩβ���num���ַ�ch, 
5.���ַ�����ĩβ����Ե�����start��end��ʾ���ַ�����. 

B==����append()��ȫ��ͬ��
basic_string &assign( const basic_string &str );
basic_string &assign( const char *str );
basic_string &assign( const char *str, size_type num );
basic_string &assign( const basic_string &str, size_type index, size_type len );
basic_string &assign( size_type num, char ch );
*/
void test2()
{    
	string str1=("hello");
	str1.append(" ");
	char* ch="world";
	str1.append(ch);
	str1.append(3,'!');
	string str2="ni hai hao ma?????";
	str1.append(str2,0,str2.length()-4);
	str1.append("veryGood!!!",5);
	cout<<str1<<endl;//hello world!!!ni hai hao ma?veryG

	string str4, str3 = "War and Peace";
	str4.assign( str3, 4, 3 );  
	cout << str4 << endl;//and
} 
//����find(),find_first_of(), find_first_not_of(),find_last_of(),find_last_not_of(),rfind()
/*
size_type find( const basic_string &str, size_type index );
size_type find( const char *str, size_type index );
size_type find( const char *str, size_type index, size_type length );
size_type find( char ch, size_type index );
find()����: 
1.����str���ַ����е�һ�γ��ֵ�λ�ã���index��ʼ���ң������û�ҵ��򷵻�string::npos, 
2.����str���ַ����е�һ�γ��ֵ�λ�ã���index��ʼ���ң�����Ϊlength�������û�ҵ��ͷ���string::npos, 
3.�����ַ�ch���ַ����е�һ�γ��ֵ�λ�ã���index��ʼ���ң������û�ҵ��ͷ���string::npos

find_first_of()����: 
1.�������ַ����е�һ����str�е�ĳ���ַ�ƥ����ַ�����������λ�á�������index��ʼ�����û�ҵ��ͷ���string::npos 
 size_type find_first_of( const char *str, size_type index, size_type num );
2.�������ַ����е�һ����str�е�ĳ���ַ�ƥ����ַ�����������λ�á�������index��ʼ���������num���ַ������û�ҵ��ͷ���string::npos�� 
3.�������ַ����е�һ����chƥ����ַ�����������λ�á�������index��ʼ�� 

find_first_not_of()����: 
1.���ַ����в��ҵ�һ����str�е��ַ�����ƥ����ַ�����������λ�á�������index��ʼ�����û�ҵ��ͷ���string::nops 
size_type find_first_not_of( const char *str, size_type index, size_type num );
2.���ַ����в��ҵ�һ����str�е��ַ�����ƥ����ַ�����������λ�á�������index��ʼ��������num���ַ������û�ҵ��ͷ���string::nops 
3.���ַ����в��ҵ�һ����ch��ƥ����ַ�����������λ�á�������index��ʼ�����û�ҵ��ͷ���string::nops 

find_last_of()����: 
1.���ַ����в������һ����str�е�ĳ���ַ�ƥ����ַ�����������λ�á�������index��ʼ�����û�ҵ��ͷ���string::nops 
 size_type find_last_of( const char *str, size_type index, size_type num );
2.���ַ����в������һ����str�е�ĳ���ַ�ƥ����ַ�����������λ�á�������index��ʼ���������num���ַ������û�ҵ��ͷ���string::nops 
3.���ַ����в������һ����chƥ����ַ�����������λ�á�������index��ʼ�����û�ҵ��ͷ���string::nops 

find_last_not_of()����: 
1.���ַ����в������һ����str�е��ַ�����ƥ����ַ�����������λ�á�������index��ʼ�����û�ҵ��ͷ���string::nops 
 size_type find_last_not_of( const char *str, size_type index, size_type num );
2.���ַ����в������һ����str�е��ַ�����ƥ����ַ�����������λ�á�������index��ʼ��������num���ַ����û�ҵ��ͷ���string::nops 
3.���ַ����в������һ����ch��ƥ����ַ�����������λ�á�������index��ʼ�����û�ҵ��ͷ���string::nops 
 
size_type rfind( const basic_string &str, size_type index );
size_type rfind( const char *str, size_type index );
size_type rfind( const char *str, size_type index, size_type num );
size_type rfind( char ch, size_type index );
rfind()����: 
1.�������һ����str�е�ĳ���ַ�ƥ����ַ�����index��ʼ���ҡ����û�ҵ��ͷ���string::npos 
2.�������һ����str�е�ĳ���ַ�ƥ����ַ�����index��ʼ����,������num���ַ������û�ҵ��ͷ���string::npos 
3.�������һ����chƥ����ַ�����index��ʼ���ҡ����û�ҵ��ͷ���string::npos 
*/
void test3()
{  
	string str1( "Alpha Beta Gamma Delta" );
	unsigned int loc = str1.find( "Omega", 0 );
	if( loc != string::npos )
		cout << "Found Omega at " << loc << endl;
	else
		cout << "Didn't find Omega" << endl;

/*	���磬�����д����е�һ�ε���rfind()����string::npos,��ΪĿ����ﲻ�ڿ�ʼ��8���ַ��С�Ȼ�����ڶ��ε��÷���9����ΪĿ������ڿ�ʼ��20���ַ�֮�С� */
	int loc2;
	string s = "My cat's breath smells like cat food.";
	loc2 = s.rfind( "breath", 8 );
	cout << "The word breath is at index " << loc2 << endl;//-1
	loc2 = s.rfind( "breath", 20 );
	cout << "The word breath is at index " << loc2 << endl;//9
}  
//����(insert),�滻(replace) 
/*
iterator insert( iterator i, const char &ch );
basic_string &insert( size_type index, const basic_string &str );
basic_string &insert( size_type index, const char *str );
basic_string &insert( size_type index1, const basic_string &str, size_type index2, size_type num );
basic_string &insert( size_type index, const char *str, size_type num );
basic_string &insert( size_type index, size_type num, char ch );
void insert( iterator i, size_type num, const char &ch );
void insert( iterator i, iterator start, iterator end );
insert()�����Ĺ��ܷǳ���: 
1.�ڵ�����i��ʾ��λ��ǰ�����һ���ַ�ch, 
2.���ַ�����λ��index�����ַ���str, 
3.���ַ�����λ��index�����ַ���str���Ӵ�(��index2��ʼ����num���ַ�), 
4.���ַ�����λ��index�����ַ���str��num���ַ�, 
5.���ַ�����λ��index����num���ַ�ch�Ŀ���, 
6.�ڵ�����i��ʾ��λ��ǰ�����num���ַ�ch�Ŀ���, 
7.�ڵ�����i��ʾ��λ��ǰ�����һ���ַ�����start��ʼ����end����. 

basic_string &replace( size_type index, size_type num, const basic_string &str );
basic_string &replace( size_type index1, size_type num1, const basic_string &str, size_type index2,
size_type num2 );
basic_string &replace( size_type index, size_type num, const char *str );
basic_string &replace( size_type index, size_type num1, const char *str, size_type num2 );
basic_string &replace( size_type index, size_type num1, size_type num2, char ch );
basic_string &replace( iterator start, iterator end, const basic_string &str );
basic_string &replace( iterator start, iterator end, const char *str );
basic_string &replace( iterator start, iterator end, const char *str, size_type num );
basic_string &replace( iterator start, iterator end, size_type num, char ch );
replace()����: 
1.��str�е�num���ַ��滻���ַ����е��ַ�,��index��ʼ 
2.��str�е�num2���ַ�����index2��ʼ���滻���ַ����е��ַ�����index1��ʼ�����num1���ַ� 
3.��str�е�num���ַ�����index��ʼ���滻���ַ����е��ַ� 
4.��str�е�num2���ַ�����index2��ʼ���滻���ַ����е��ַ�����index1��ʼ��num1���ַ� 
5.��num2��ch�ַ��滻���ַ����е��ַ�����index��ʼ 
6.��str�е��ַ��滻���ַ����е��ַ�,������start��endָʾ��Χ 
7.��str�е�num���ַ��滻���ַ����е�����,������start��endָʾ��Χ�� 
8.��num��ch�ַ��滻���ַ����е����ݣ�������start��endָʾ��Χ. 
*/
void test4()
{   
	string s = "They say he carved it himself...from a BIGGER spoon";
	string s2 = "find your Homer.";
	s.replace( 32, s2.length(), s2 );
	cout << s << endl;   //They say he carved it himself...find your Homer.oon
}  
//����
/*
����(swap)  void swap( basic_string &str );//��str�ͱ��ַ�������
 
basic_string substr( size_type index, size_type num = npos );
substr()���ر��ַ�����һ���Ӵ�����index��ʼ����num���ַ������û��ָ��������Ĭ��ֵ string::npos��������substr()�������򵥵ķ��ش�index��ʼ��ʣ����ַ�����

size_type size();//size()���������ַ���������ӵ�е��ַ�����
size_type length();//length()���������ַ����ĳ���. �������Ӧ�ú�size()���ص�������ͬ.

void clear();//���
bool empty();//����ַ���Ϊ����empty()������(true)�����򷵻ؼ�(false).

const char *data();//data()��������ָ���Լ��ĵ�һ���ַ���ָ��.
const char *c_str();//c_str()��������һ��ָ������C�ַ�����ָ��, �����뱾�ַ�����ͬ. 
*/
void test5()
{   
	string first( "This comes first" );
	string second( "And this is second" );
	first.swap( second );
	cout << first << endl;//And this is second
	cout << second << endl;//This comes first

	string s("What we have here is a failure to communicate");
	string sub = s.substr(5); 
	cout << sub << endl;//we have here is a failure to communicate

	cout<<"sub size:"<<sub.size()<<"  len:"<<sub.length()<<endl;//40 40
		
	//sub.clear();//<==>sub="";
	cout<<sub.empty()<<endl;//1  

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