#include <iostream>

#include <stdlib.h>

#include <time.h>

#include <algorithm>

#include <functional>

#include <vector>

#include<iterator>

using namespace std;

 

void Display(vector<int>& vr, const char* s);

unsigned int RandInt(const unsigned int n);

 

int main()

{

int iarray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

vector<int> v(iarray, iarray + 10);

 

srand(time(NULL));

Display(v, "Before shuffle:");

 

//Converts a unary function pointer into an adaptable unary function.

pointer_to_unary_function<unsigned int, unsigned int> ptr_RandInt =

ptr_fun(RandInt);

//对一个元素序列进行重新排序（随机的），包含在头文件 algorithm.h中

random_shuffle(v.begin(), v.end(), ptr_RandInt);

Display(v,"After shuffle:");

system("pause");

return 0;

}

 

/// 显示

void Display(vector<int>& vr, const char* s)

{

cout << endl << s << endl;

copy(vr.begin(), vr.end(), ostream_iterator<int>(cout, " "));

cout << endl;

}

 

//返回随机值

unsigned int RandInt(const unsigned int n)

{

return rand() % n;

}