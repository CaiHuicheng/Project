class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet;
        for(auto word:wordDict){
            wordSet.insert(word);
        }

        vector<bool> dp(s.size()+1);
        dp[0] = true;
        for(int i=1;i<=s.size();i++){
            for(int j = 0;j<i;j++){
                if(dp[j]&&wordSet.find(s.substr(j,i-j))!=wordSet.end()){
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};