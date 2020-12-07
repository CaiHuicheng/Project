class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        int m = A.size(),n = A[0].size();
        int res = m*(1<<(n-1));
        for(int j = 1;j<n;j++){
            int  temp = 0;
            for(int i = 0;i<m;i++){
                if(A[i][0] == 1){
                    temp+=A[i][j];
                }
                else{
                    temp+=(1-A[i][j]);//行翻转
                }
            }
            int k = max(temp,m-temp);
            res += k*(1<<(n-j-1));
        }
        return res;
    }
};