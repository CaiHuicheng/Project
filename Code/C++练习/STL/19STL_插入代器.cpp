#include <iostream>

#include <algorithm>

#include <list>

#include <iterator>

using namespace std;

 

void Display(list<int>& a, const char* s)

{

cout << s << endl;

copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));

cout << endl;

}

 

int main()

{

int iArray[5] = { 1, 2, 3, 4, 5 };

list<int> iList;

//使用copy函数把数组中值复制到STL容器，复制的时候利用前端插入，插入后，再在前面插入

// 若插入 1，再插入2，就变成了2，1

copy(iArray, iArray + 5, front_inserter(iList));

Display(iList, "Before find and copy ");

 

// 定义list容器迭代器，找到3的位置初始化迭代器，当前list容器的迭代器是（5，4，3，2，1）

list<int>::iterator p = find(iList.begin(), iList.end(), 3);

 

// 将数组的前两个元素插入到容器，插入位置为之前找到3的位置之前

copy(iArray, iArray + 2, inserter(iList, p));

Display(iList, "After find and copy");

 

system("pause");

return 0;

}