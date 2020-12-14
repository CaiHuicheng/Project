class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n+1,INT_MAX);
        dp[0] = 0;
        for(int i =1,sqr = i*i;sqr<=n;i++,sqr = i*i){
            for(int j = sqr;j<=n;++j){
                dp[j] = min(dp[j],dp[j-sqr]+1);
            }
        }
        return dp[n];
    }
};