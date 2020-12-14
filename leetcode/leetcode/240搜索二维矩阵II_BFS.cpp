class Solution {
public:
    int m,n;
    int N=999999;

    bool dfs(vector<vector<int>>& matrix,int x,int y,int target){
        if(x<0||x>=m||y<0||y>=n) return false;
        if(matrix[x][y]==N) return false;
        if(matrix[x][y]==target) return true;
        if(matrix[x][y]>target) return false;
        matrix[x][y]=N;
        bool test1=dfs(matrix,x+1,y,target);
        bool test2=dfs(matrix,x,y+1,target);
        return test1||test2;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m=matrix.size();
        if(m==0) return false;
        n=matrix[0].size();
        if(n==0) return false;
        return dfs(matrix,0,0,target);
    }
};
