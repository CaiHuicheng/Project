

#include <conio.h> 
#include <iostream>
#include <string>
using namespace std; 
//1.构造函数
/*
string();
string( size_type length, char ch );
string( const char *str );
string( const char *str, size_type index );
string( string &str, size_type index, size_type length );
string( input_iterator start, input_iterator end );
字符串的构造函数创建一个新字符串，包括: 
1.以length为长度的ch的拷贝（即length个ch） 
2.以str为初值 (长度任意), 
3.以index为索引开始的子串，长度为length,或者 
4.以从start到end的元素为初值.
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
//2.操作符
/*
1.用==, >, <, >=, <=, and !=比较字符串,compare()
2.用 + 或者 += 操作符连接两个字符串
3.用[]获取特定的字符-->at()
A.compare()
int compare( const basic_string &str );
int compare( const char *str );
int compare( size_type index, size_type length, const basic_string &str );
int compare( size_type index, size_type length, const basic_string &str, size_type index2,
size_type length2 );
int compare( size_type index, size_type length, const char *str, size_type length2 );
返回值 情况 :小于零 this < str ;零 this == str ;大于零 this > str 
不同的函数: 
1.比较自己和str, 
2.比较自己的子串和str,子串以index索引开始，长度为length 
3.比较自己的子串和str的子串，其中index2和length2引用str，index和length引用自己 
4.比较自己的子串和str的子串，其中str的子串以索引0开始，长度为length2，自己的子串以index开始，长度为length 
*/
void test1()
{ 	 
	string str1("hello"); 
	cout<<str1[1]<<"  "<<str1.at(4)<<endl;//e o //注意下标不要出界，否则会崩溃
} 
//添加文本 append();赋值assign()
/*
basic_string &append( const basic_string &str );
basic_string &append( const char *str );
basic_string &append( const basic_string &str, size_type index, size_type len );
basic_string &append( const char *str, size_type num );
basic_string &append( size_type num, char ch );
append() 函数可以完成以下工作: 
1.在字符串的末尾添加str, 
2.在字符串的末尾添加str的子串,子串以index索引开始，长度为len 
3.在字符串的末尾添加str中的num个字符, 
4.在字符串的末尾添加num个字符ch, 
5.在字符串的末尾添加以迭代器start和end表示的字符序列. 

B==》与append()完全相同。
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
//查找find(),find_first_of(), find_first_not_of(),find_last_of(),find_last_not_of(),rfind()
/*
size_type find( const basic_string &str, size_type index );
size_type find( const char *str, size_type index );
size_type find( const char *str, size_type index, size_type length );
size_type find( char ch, size_type index );
find()函数: 
1.返回str在字符串中第一次出现的位置（从index开始查找）。如果没找到则返回string::npos, 
2.返回str在字符串中第一次出现的位置（从index开始查找，长度为length）。如果没找到就返回string::npos, 
3.返回字符ch在字符串中第一次出现的位置（从index开始查找）。如果没找到就返回string::npos

find_first_of()函数: 
1.查找在字符串中第一个与str中的某个字符匹配的字符，返回它的位置。搜索从index开始，如果没找到就返回string::npos 
 size_type find_first_of( const char *str, size_type index, size_type num );
2.查找在字符串中第一个与str中的某个字符匹配的字符，返回它的位置。搜索从index开始，最多搜索num个字符。如果没找到就返回string::npos， 
3.查找在字符串中第一个与ch匹配的字符，返回它的位置。搜索从index开始。 

find_first_not_of()函数: 
1.在字符串中查找第一个与str中的字符都不匹配的字符，返回它的位置。搜索从index开始。如果没找到就返回string::nops 
size_type find_first_not_of( const char *str, size_type index, size_type num );
2.在字符串中查找第一个与str中的字符都不匹配的字符，返回它的位置。搜索从index开始，最多查找num个字符。如果没找到就返回string::nops 
3.在字符串中查找第一个与ch不匹配的字符，返回它的位置。搜索从index开始。如果没找到就返回string::nops 

find_last_of()函数: 
1.在字符串中查找最后一个与str中的某个字符匹配的字符，返回它的位置。搜索从index开始。如果没找到就返回string::nops 
 size_type find_last_of( const char *str, size_type index, size_type num );
2.在字符串中查找最后一个与str中的某个字符匹配的字符，返回它的位置。搜索从index开始，最多搜索num个字符。如果没找到就返回string::nops 
3.在字符串中查找最后一个与ch匹配的字符，返回它的位置。搜索从index开始。如果没找到就返回string::nops 

find_last_not_of()函数: 
1.在字符串中查找最后一个与str中的字符都不匹配的字符，返回它的位置。搜索从index开始。如果没找到就返回string::nops 
 size_type find_last_not_of( const char *str, size_type index, size_type num );
2.在字符串中查找最后一个与str中的字符都不匹配的字符，返回它的位置。搜索从index开始，最多查找num个字符如果没找到就返回string::nops 
3.在字符串中查找最后一个与ch不匹配的字符，返回它的位置。搜索从index开始。如果没找到就返回string::nops 
 
size_type rfind( const basic_string &str, size_type index );
size_type rfind( const char *str, size_type index );
size_type rfind( const char *str, size_type index, size_type num );
size_type rfind( char ch, size_type index );
rfind()函数: 
1.返回最后一个与str中的某个字符匹配的字符，从index开始查找。如果没找到就返回string::npos 
2.返回最后一个与str中的某个字符匹配的字符，从index开始查找,最多查找num个字符。如果没找到就返回string::npos 
3.返回最后一个与ch匹配的字符，从index开始查找。如果没找到就返回string::npos 
*/
void test3()
{  
	string str1( "Alpha Beta Gamma Delta" );
	unsigned int loc = str1.find( "Omega", 0 );
	if( loc != string::npos )
		cout << "Found Omega at " << loc << endl;
	else
		cout << "Didn't find Omega" << endl;

/*	例如，在下列代码中第一次调用rfind()返回string::npos,因为目标词语不在开始的8个字符中。然而，第二次调用返回9，因为目标词语在开始的20个字符之中。 */
	int loc2;
	string s = "My cat's breath smells like cat food.";
	loc2 = s.rfind( "breath", 8 );
	cout << "The word breath is at index " << loc2 << endl;//-1
	loc2 = s.rfind( "breath", 20 );
	cout << "The word breath is at index " << loc2 << endl;//9
}  
//插入(insert),替换(replace) 
/*
iterator insert( iterator i, const char &ch );
basic_string &insert( size_type index, const basic_string &str );
basic_string &insert( size_type index, const char *str );
basic_string &insert( size_type index1, const basic_string &str, size_type index2, size_type num );
basic_string &insert( size_type index, const char *str, size_type num );
basic_string &insert( size_type index, size_type num, char ch );
void insert( iterator i, size_type num, const char &ch );
void insert( iterator i, iterator start, iterator end );
insert()函数的功能非常多: 
1.在迭代器i表示的位置前面插入一个字符ch, 
2.在字符串的位置index插入字符串str, 
3.在字符串的位置index插入字符串str的子串(从index2开始，长num个字符), 
4.在字符串的位置index插入字符串str的num个字符, 
5.在字符串的位置index插入num个字符ch的拷贝, 
6.在迭代器i表示的位置前面插入num个字符ch的拷贝, 
7.在迭代器i表示的位置前面插入一段字符，从start开始，以end结束. 

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
replace()函数: 
1.用str中的num个字符替换本字符串中的字符,从index开始 
2.用str中的num2个字符（从index2开始）替换本字符串中的字符，从index1开始，最多num1个字符 
3.用str中的num个字符（从index开始）替换本字符串中的字符 
4.用str中的num2个字符（从index2开始）替换本字符串中的字符，从index1开始，num1个字符 
5.用num2个ch字符替换本字符串中的字符，从index开始 
6.用str中的字符替换本字符串中的字符,迭代器start和end指示范围 
7.用str中的num个字符替换本字符串中的内容,迭代器start和end指示范围， 
8.用num个ch字符替换本字符串中的内容，迭代器start和end指示范围. 
*/
void test4()
{   
	string s = "They say he carved it himself...from a BIGGER spoon";
	string s2 = "find your Homer.";
	s.replace( 32, s2.length(), s2 );
	cout << s << endl;   //They say he carved it himself...find your Homer.oon
}  
//其他
/*
交换(swap)  void swap( basic_string &str );//把str和本字符串交换
 
basic_string substr( size_type index, size_type num = npos );
substr()返回本字符串的一个子串，从index开始，长num个字符。如果没有指定，将是默认值 string::npos。这样，substr()函数将简单的返回从index开始的剩余的字符串。

size_type size();//size()函数返回字符串中现在拥有的字符数。
size_type length();//length()函数返回字符串的长度. 这个数字应该和size()返回的数字相同.

void clear();//清空
bool empty();//如果字符串为空则empty()返回真(true)，否则返回假(false).

const char *data();//data()函数返回指向自己的第一个字符的指针.
const char *c_str();//c_str()函数返回一个指向正规C字符串的指针, 内容与本字符串相同. 
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