class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // int minN = prices[0],maxN = 0;
        // for(auto price:prices){
        //     maxN = max(maxN,price-minN);
        //     minN = min(minN,price); 
        // }
        // return maxN;
        int n = prices.size();
        if(n == 0) return 0;
         int minN = prices[0];
        vector<int> dp(n,0);
        for(int i = 1;i<n;i++){
            minN = min(minN,prices[i]);
            dp[i] = max(dp[i-1],prices[i]-minN);
        }
        return dp[n-1];
    }
};
};