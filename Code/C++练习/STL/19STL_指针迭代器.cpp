#include <iostream>

#include <algorithm>

using namespace std;

 

#define SIZE 100

int iarray[SIZE];

 

int main()

{

iarray[20] = 50;

int* ip = find(iarray, iarray + SIZE, 50);

if (ip == iarray + SIZE)//如果指针指向数组的尾部，就表示没有找到

cout << "50 not found in array" << endl;

else

cout << *ip << " found in array" << endl;

 

system("pause");

return 0;

}