/*
  1 #include <iostream>
  2 using namespace std;
  3 
  4 int func1(int a=0;int b)
  5 {
  6     return a+b;
  7 }
  8 int sum()
  9 {
 10     int sum;
 11     int* const point1;
 12     int const* point2;
 13     point1=&sum
 14     point2=func1(3,4);
 15     int i=1,j=2;
 16     for(i,j;i<10,j<10;i++,j++)
 17     {
 18          sum+=func1(i,j);
 19      }
 20     return *point1;
 21 }
 22 int main(int argc, char *argv[])
 23 {
 24     int ret= sum();
 25     cout << ret;
 26     return 0;
 27 }

第4行：func1(int a=0;int b) //函数传参使用的是','非';'，即修改为​
func1(int a=0,int b)
第8行： sum没有初始化

第13行： 缺少；即改为：
point1=&num;
第14行:  返回值不对，func1返回值为int，point2为const int*类型

修改后代码：
*/



#include <iostream>
using namespace std;
  
 int func1(int a,int b)
 {
     return a+b;
 }
 int sum()
 {
     int sum = 0 ;
     int* const point1 = &sum;
 
     int i=1,j=2;
     for(i,j; i<8,j<11; i = i + 2,j = j + 2)
     {
          sum+=func1(i,j);
     }
    return *point1;
 }
 int main(int argc, char *argv[])
 {
     int ret= sum();
     cout << ret;
     return 0;
}