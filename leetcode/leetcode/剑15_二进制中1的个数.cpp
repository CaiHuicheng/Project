class Solution {
public:
    int hammingWeight(uint32_t n) {
        // int count = 0;
        // while(0!=n){
        //     count += n & 1;
        //     n =n>>1;
        // }
        // return count;
        return n?1+hammingWeight(n & (n-1)):0;
    }
};