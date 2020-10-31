#include <iostream>

#include <algorithm>

#include <functional>

#include <list>

using namespace std;

 

/*

bind1st() 创建一个函数对象，函数对象将值V作为第一个参数A

bind2nd() 创建一个函数对象，函数对象将值V作为第二个参数B

*/

 

int main()

{

int iarray[10] = { 1, 2, 11, 4, 34, 6, 7, 8, 9, 10 };

list<int> aList(iarray, iarray + 10);

 

int k = 0;

/*

 

typename iterator_traits<_InIt>::difference_type

count_if(_InIt _First, _InIt _Last, _Pr _Pred)

{// count elements satisfying _Pred

_DEBUG_RANGE(_First, _Last);

_DEBUG_POINTER(_Pred);

return (_Count_if(_Unchecked(_First), _Unchecked(_Last), _Pred));

}

*/

// count_if() 计算满足特定条件的元素的数目

k = count_if(aList.begin(), aList.end(), bind1st(greater<int>(), 8));

cout << "Number elements < 8 ==" << k << endl;

system("pause");

return 0;

}