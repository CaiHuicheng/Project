#include <iostream>

#include <stdlib.h>

#include <stdio.h>

#include <time.h>

#include <vector>

#include <algorithm>

using namespace std;

 

#define VSIZE 10

vector<long> v(VSIZE);

 

void initialize(long &ri);

void show(const long &ri);

bool isMinus(const long &ri);

 

int main()

{

srand(time(NULL));// 初始化随机发生器种子

 

for_each(v.begin(), v.end(), initialize); //遍历容器，调用普通函数赋值操作

cout << "Vector of signal long itergers" << endl;

for_each(v.begin(), v.end(), show); // 编译容器，并显示

cout << endl;

 

int count = 0;

vector<long>::iterator p;

// 调用断言函数,如果容器中存在小于0的数，则返回第一个小于0 的迭代器

p = find_if(v.begin(), v.end(), isMinus);

//cout << *p << endl;

// 统计小于0 的数的个数

while (p != v.end())

{

count++;

p = find_if(p + 1, v.end(), isMinus);

}

cout << "Number of values:" << VSIZE << endl;

cout << "Negative valuses:" << count << endl;

 

system("pause");

return 0;

}
/ 利用随机数获得值

void initialize(long &ri)

{

ri = (rand() - (RAND_MAX / 2));

}

 

// 显示

void show(const long &ri)

{

cout << ri << " ";

}

 

// 判断小于0的数，返回为真

bool isMinus(const long &ri)

{

return (ri < 0);

}