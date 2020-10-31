#include <iostream>
#include <set>
  
using namespace std;
  
//抽象一个函数，用来输出集合set中的值
void print(set<int> seta)
{
 set<int >::iterator itor = seta.begin();
 while(itor != seta.end())
 {
  cout << "set内的值为：" << *itor << endl;
  itor++;
 }
}
  
int main()
{
 set<int> seta;
 cout << "初始化前set的大小：" << seta.size() << endl;
 cout << "初始化前set是否为空： " << seta.empty() << endl;
  
 //初始化set
 //用insert函数初始化
 for(int i = 0; i < 10; i++)
 {
  seta.insert(i);
 }
  
 /*
 //这里也可以使用数组来赋值进行初始化
 int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
 set<int> seta(a,a+10);
 */
  
 cout << "初始化后set的大小：" << seta.size() << endl;
 cout << "初始化后set是否为空： " << seta.empty() << endl;
  
 print(seta);
  
 //测试find函数
 if(seta.find(0) == seta.end())
 {
  cout << "0不存在" << endl;
 }else{cout << "0存在" << endl;}
  
 if(seta.find(11) != seta.end())
 {
  cout << "11存在" << endl;
 }else{cout << "11不存在" << endl;}
  
 //测试erase函数
 seta.erase(9);
 cout << "删除9之后seta的值： " << endl;
 print(seta);
  
 //测试插入函数insert
 int a[5] = {11, 12, 13, 14, 15};
 seta.insert(a,a+5);
 cout << "插入后seta的值: " << endl;
 print(seta);
  
  
  
 return 0;
}
