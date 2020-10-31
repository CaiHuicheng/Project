#include <iostream>

#include <numeric>

#include <vector>

#include <functional>

 

using namespace std;

 

#define MAX 10

vector<long> v(MAX);

 

int main()

{

//初始化容器容器中的元素

for (int i = 0; i < 10; i++)

v[i] = i + 1;

// accumulate函数对容器内元素求和，头文件numeric

long sum = accumulate(v.begin(), v.end(), 0);

cout << "Sum of values ==" << sum << endl;

 

//  函数模板acumulate利用multiplies仿函数（头文件functional）对容器内元素进行连续相乘操作

long product = accumulate(v.begin(), v.end(),1, multiplies<long>());

cout << "Product of values ==" << product << endl;

 

system("pause");

return 0;

}