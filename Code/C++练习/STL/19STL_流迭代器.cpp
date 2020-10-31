#include <iostream>

#include <algorithm>

#include <vector>

#include <stdlib.h>

#include <time.h>

#include <iterator>

using namespace std;

 

void Display(vector<int>& v, const char* s)

{

cout << endl << s << endl;

copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));//使用流迭代器，使用“\t”隔开

cout << endl;

}

 

int main()

{

srand(time(NULL));// 用时间初始化随机发生器

vector<int> collection(10);

for (int i = 0; i < 10; i++)

collection[i] = rand() % 1000;  // 产生的随机数用1000 模运算

Display(collection, "Before sorting");//排序前输出

sort(collection.begin(), collection.end());//对容器进行排序

Display(collection, "After sorting");//排序后输出

system("pause");

return 0;

}