class Solution {
public:
    double myPow(double x, int n) {
        if(x == 1.0||n == 0) return 1.0;
        if(x == 0.0&&n < 0) return x;
        double res = 1.0;
        long exp = n;
        if(n<0){x = 1/x;exp = -exp;}
        while(exp){
            if(exp & 1)res *= x;
            x *=x;
            exp >>= 1;
        }
        return res;
    }
};