class Palindrome {
public:
    int getLongestPalindrome(string A, int n) {
        // write code here
        vector<vector<int>> dp(n, vector<int>(n));
        string ans;
        for (int l = 0; l < n; ++l) {
            for (int i = 0; i + l < n; ++i) {
                int j = i + l;
                if (l == 0) {
                    dp[i][j] = 1;
                } else if (l == 1) {
                    dp[i][j] = (A[i] == A[j]);
                } else {
                    dp[i][j] = (A[i] == A[j] && dp[i + 1][j - 1]);
                }
                if (dp[i][j] && l + 1 > ans.size()) {
                    ans = A.substr(i, l + 1);
                }
            }
        }
        return ans.size();
    }
};