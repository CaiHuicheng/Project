#include<iostream>
using namespace std;
//常量定义：1、 #define 定义在文件上方     2、用 变量前面加关键字const
//变量创建语法：数据类型 变量名 = 变量值;
constexpr auto Day = 7;

int main() {
	//Day为常量修改会报错,const修饰的也是常量

	const int month = 12;

	cout << "一周一共有" << Day <<"天"<< endl;
	cout << "一年一共有" << month << "月" << endl;

	system("pause");

	return 0;
}