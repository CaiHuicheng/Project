class Solution {
public:
    bool v[100][100];
    int movingCount(int m, int n, int k) {
        return dfs(m,n,0,0,k);
    }
    int dfs(int m,int n,int i,int j,int k){
        if(i<0||i>=m||j<0||j>=n||i%10+i/10+j%10+j/10>k||v[i][j]) return false;
        v[i][j] = true;
        return 1+dfs(m,n,i-1,j,k)+dfs(m,n,i+1,j,k)+dfs(m,n,i,j-1,k)+dfs(m,n,i,j+1,k);
    }
};