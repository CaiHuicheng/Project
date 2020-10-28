#include <fstream>
#include <iostream>
using namespace std;
int main ()
{
    char data[100]="Welcome to dotcpp";
    ofstream file;
    file.open("d:\\dotcpp.dat");
    file << data;
    file.close();   //调用close函数，关闭文件操作
    return 0;}