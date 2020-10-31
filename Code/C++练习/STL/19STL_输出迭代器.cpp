#include <iostream>

#include <algorithm>

#include <vector>

using namespace std;

 

int main()

{

double darray[10] = { 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9 };

vector<double> vdouble(10);

 

vector<double>::iterator outputInterator = vdouble.begin();//定义容器迭代器，

copy(darray, darray + 10, outputInterator);

while (outputInterator != vdouble.end())

{

cout << *outputInterator << endl;

outputInterator++;

}

system("pause");

return 0;

}