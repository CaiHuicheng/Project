#include<iostream>
#include<string>
using namespace std;

//数据类型存在的意义：给变量分配合适的内存
int main() {

	//==================整型====================

	////1、短整型
	//int num1 = 10;

	////2、整型
	//int num2 = 10;

	////3、长整型
	//int num3 = 10;

	////4、长长整型
	//int num4 = 10;

	//cout << "num(short)=" << num1 << endl;
	//cout << "num=" << num2 << endl;
	//cout << "num(long)=" << num3 << endl;
	//cout << "num(long long)=" << num4 << endl;


	////===============sizeof关键字=====================

	////利用sizeof关键字可以统计数据类型所占内存大小
	//cout << "short=" << sizeof(short) << endl;
	//cout << "int=" << sizeof(int) << endl;
	//cout << "long=" << sizeof(long) << endl;
	//cout << "long long=" << sizeof(long long) << endl;

	////==================浮点型（float 7位 double 15~16位）========================


	//float num1 = 1.58965216546464f;

	//double num2 = 1.58965216546464;
	///*cout << "float=" << num1 << endl;
	//cout << "double=" << num2 << endl;*/
	//cout << "float=" << sizeof(num1) << endl;
	//cout << "double=" << sizeof(num2) << endl;
	////科学计数法
	//float f1 = 3e2;
	//float f2 = 3e-2;

	//cout << "f1=" << f1 << endl;
	//cout << "f2=" << f2 << endl;

	//====================字符型===============

	/*char ch = 'a';

	cout << "a=" << ch << endl;
	cout << "char=" << sizeof(char) << endl;
	cout << (int)ch << endl;*/


	//===================转义字符===============
	/*警报 \a 
	退格 \b
	换页 \f
	换行 \n
	回车 \r
	水平制表 \t
	垂直制表 \v
	表示“\”\\
	表示“'” \'
	表示“"” \"*/

	//cout << "hello world\n";

	//cout << "\\"<< endl;

	//cout << "aaa\tHello World" << endl;

	

	////=====================字符串===================
	////c++风格 string 变量名 = "变量值";  要头文件 #include<string>
	//string hello = "Hello World!!!";
	//cout << hello << endl;
	////======================布尔类型================
	//bool flag = true;
	//cout << flag << endl;//输出1

	//1、整型和浮点型键盘输入输出

	/*int a = 0;
	cout << "请给整型变量a赋值：" << endl;
	cin >> a;
	cout << "整型数据类型a = " << a << endl;*/

	/*float f = 0.0f;
	cout << "请给浮点型变量f赋值：" << endl;
	cin >> f;
	cout << "浮点型数据类型f = " << f << endl;
	system("pause");*/


	return 0;
}