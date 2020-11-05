class Solution {
public:
    int longestValidParentheses(string s) {
        /*
        状态转移方程：
            //s[i-1] == '(',即有“.....()”
            dp[i] = dp[i-2] + 2 
            //s[i-1] = ')',既有"......))"
            s[i-dp[i-1]-1] == '(' => dp[i] = dp[i-1]+dp[i-dp[i-1]-2]+2
        
        边界条件：
            i - 2 有可能小于零越界了，这种情况下就是只有 () ，前面记为 0 就好了.
            i - dp[i - 1] - 1 和 i - dp[i - 1] - 2 都可能越界，越界了当成 0 来计算就可以了.
        */
        int maxLen = 0;
        vector<int> dp(s.length());
        for(int i = 1;i < s.length();i++){
            if(s[i] == ')'){
                if(s[i-1] == '('){
                    dp[i] = (i-2>=0?dp[i-2]:0)+2;
                }else if(i-dp[i-1]-1>=0 && s[i-dp[i-1]-1] == '('){
                    dp[i] = (i-dp[i-1]-2>=0?dp[i-dp[i-1]-2]:0)+dp[i-1]+2;
                }
            }
            maxLen  = fmax(dp[i],maxLen);
        }
        return maxLen;
    }
};