#include <iostream>

#include <algorithm>

#include <vector>

using namespace std;

 

int main()

{

vector<int> intVector(100);

intVector[20] = 50;

vector<int>::iterator intIter = find(intVector.begin(), intVector.end(), 50);

if (intIter != intVector.end())

cout << "Vector contains value" << *intIter << endl;

else

cout << "Vector does not contain 50" << endl;

 

system("pause");

return 0;