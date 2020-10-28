#include <fstream>
#include <iostream>
using namespace std;
int main ()
{
    char data[100]="Welcome to dotcpp";
    ofstream file;
    file.open("d:\\dotcpp.dat");
    file << data;
    file.close();
    return 0;
}