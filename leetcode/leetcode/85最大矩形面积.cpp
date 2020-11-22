class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        if(n == 0) return 0;
        int maxArea = 0;
        int m=matrix[0].size();
        vector<vector<int>> dp(n,vector<int>(m,0));
        for(int i=0;i<n;i++){
            for(int j= 0;j<m;j++){
                if(matrix[i][j] == '1'){
                    dp[i][j] = j==0?1:dp[i][j-1]+1;
                    int w = dp[i][j];
                    for(int k=i;k>=0;k--){
                        w = min(w,dp[k][j]);
                        maxArea = max(maxArea,w*(i-k+1));
                    }
                }
            }
        } 
        return maxArea;
    }
};