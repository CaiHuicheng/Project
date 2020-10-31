#include <iostream>

#include <list>

#include <iterator>

using namespace std;

 

/*

advance()   按指定的数目增减迭代器

distance()  返回到达一个迭代器所需（递增）操作的数目

*/

 

void Display(list<int>& v, const char* s)

{

cout << endl;

cout << s << endl;

copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));

cout << endl;

}

 

int main()

{

int iArray[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

list<int> iList;

list<int>::iterator p = iList.begin(); //定义迭代器并指向容器开始

copy(iArray, iArray + 10, inserter(iList, p));//从p开始插入

//copy(iArray, iArray + 10, front_inserter(iList));//前端插入

Display(iList, "Before");

p = find(iList.begin(), iList.end(), 2);

cout << "before:p==" << *p << endl;

advance(p, 2);//p+=2

cout << "after:p==" << *p << endl;

 

int k = 0;

p = iList.begin();

k = distance(p, iList.end());//等价于iList.end()-p,

cout << "k==" << k << endl;

system("pause");

return 0;

}