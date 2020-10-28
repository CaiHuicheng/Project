class Solution {
public:
    bool isMatch(string s, string p) {
        if(p.empty()) return s.empty();
        s = " "+ s;
        p = " "+ p;
        int m = s.size(),n = p.size();
        vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
        dp[0][0] = true;
        for(int i = 1;i < m+1;i++){
            for(int j = 1;j < n+1; j++){
                if(s[i-1] == p[j-1]||p[j-1] == '.'){
                    dp[i][j] = dp[i-1][j-1];
                }else if(p[j-1] == '*'){
                    if(s[i-1] != p[j-2]&&p[j-2] != '.'){
                        dp[i][j] = dp[i][j-2];
                    }else{
                        dp[i][j] = dp[i][j-2]||dp[i-1][j];
                    }
                }
            }
        }
        return dp[m][n];
    }
};