#include <iostream>

#include <algorithm>

#include <vector>

#include <iterator>

#include <functional>

using namespace std;

 

/*

FiboRand模板函数对象类，继承自unary_function<Arg,Arg>

该类定义了两个成员函数，一个是构造函数，另一是operator()()函数，

该操作符允许random_shuffle()算法像一个函数一样“调用"一个FiboRand对象。

*/

template <typename Arg>

class FiboRand :public unary_function<Arg, Arg>

{

int i, j;

Arg sequence[18];

public:

FiboRand();

Arg operator()(const Arg& arg);

};

 

 

template<typename Arg>

FiboRand<Arg>::FiboRand()

{

sequence[17] = 1;

sequence[16] = 2;

for (int n = 15; n >= 0; n--)

sequence[n] = sequence[n + 1] + sequence[n + 2];

i = 17;

j = 5;

/*

for (i = 0; i < 18; ++i)

cout << sequence[i] << " ";

cout << endl;

*/

}

 

template<typename Arg>

Arg FiboRand<Arg>::operator()(const Arg& arg)

{

Arg k = sequence[i] + sequence[j];

sequence[i] = k;

i--;

j--;

if (i == 0) i = 17;

if (j == 0) j = 17;

return k%arg;

}

 

void Display(vector<int>& vr, const char* s)

{

cout << endl << s << endl;

copy(vr.begin(), vr.end(), ostream_iterator<int>(cout, " "));

cout << endl;

}

 

 

int main()

{

int iarray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

vector<int> v(iarray, iarray + 10);

 

FiboRand<int> fibogen; //construct generator object

cout << "Fibonacci random number generator" << endl;

cout << "using random_shuffle and a  function object" << endl;

Display(v, "Before shuffle:");

random_shuffle(v.begin(), v.end(), fibogen);

Display(v, "After shuffle:");

 

system("pause");

return 0;

}