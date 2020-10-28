#include <fstream>
#include <iostream>
using namespace std;
int main ()
{
 
   char data[100];
   // 以写模式打开文件
   ifstream file;
    file.open("d:\\dotcpp.dat");
    file >> data;
    cout<<data;
   // 关闭打开的文件
   file.close();
   return 0;}