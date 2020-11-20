#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int uniquePaths(int m,int n){
        /*
        机器人一定会走m+n-2步，即从m+n-2中挑出m-1步向下走,或者n-1步向向右走
        每一个组合对应一条路径，使用排列组合，结果即为C((m+n-2),min(m-1)(n-1))。
        */
        int N = n+m-2;
        int k = min(m-1,n-1);
        long long res = 1;
        for(int i = 1;i <= k;i++){
            res = res*(N-k+i)/i;
        }
        return (int)res;
    }
};

int main() {
    Solution s;
    int m =3 ,n = 2;
    int nums = s.uniquePaths(m,n);
    cout<<nums<<endl;
    return 0;
}