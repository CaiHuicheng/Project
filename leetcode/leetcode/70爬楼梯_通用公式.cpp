class Solution {
public:
    int climbStairs(int n) {
       double sqrt5 = sqrt(5);
       double num = pow((1+sqrt5)/2,n+1)-pow((1-sqrt5)/2,n+1);
       return (int)(num/sqrt5);
    }
};
