#include "stdafx.h"  
#include <cv.h>  
#include <vector>   
#include <iostream>   
using namespace std;  
int main()  
{  
    using namespace std;  
    int out[3][2] = { 1, 2,   
             3, 4,  
            5, 6 };  
    vector <int*> v1;  
    v1.push_back(out[0]);  
    v1.push_back(out[1]);  
    v1.push_back(out[2]);  
    cout << v1[0][0] << endl;//1  
    cout << v1[0][1] << endl;//2  
    cout << v1[1][0] << endl;//3  
    cout << v1[1][1] << endl;//4  
    cout << v1[2][0] << endl;//5  
    cout << v1[2][1] << endl;//6  
    return 0;  
}  