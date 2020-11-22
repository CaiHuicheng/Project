class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int n = matrix.size();
        if(n == 0) return 0;
        int maxArea = 0;
        int m=matrix[0].size();
        vector<int> dp(m,0);
        for(int i=0;i<n;i++){
            for(int j= 0;j<m;j++){
                dp[j] = matrix[i][j]=='1'?dp[j]+1:0;
            }
            maxArea = max(maxArea,max_area(dp));
        } 
        return maxArea;
    }
    int max_area(vector<int>& dp){
        stack<int> s;
        s.push(-1);
        int maxArea = 0,h=0,w = 0,n=dp.size();
        for(int i=0;i<n;++i){
            while(s.top()!=-1&&dp[i]<=dp[s.top()]){
                h = dp[s.top()];
                s.pop();
                w = i-s.top()-1;
                maxArea = max(maxArea,h*w);
            }
            s.push(i);
        }
        while(s.top()!=-1){
            h = dp[s.top()];
            s.pop();
            w = dp.size()-s.top()-1;
            maxArea = max(maxArea,h*w);
        }
        return maxArea;
    }
};