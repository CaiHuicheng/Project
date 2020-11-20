class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.size() == 0||grid[0].size() == 0) return 0;
        int rows = grid.size(),cols = grid[0].size();
        for(int i = 1;i<rows;i++){
            grid[i][0] += grid[i-1][0];
        }
        for(int j = 1;j<cols;j++){
            grid[0][j] += grid[0][j-1];
        }
        for(int i = 1;i<rows;i++){
            for(int j = 1;j<cols;j++){
                grid[i][j] += min(grid[i-1][j],grid[i][j-1]);   
            }
        }
        return grid[rows-1][cols-1];
    } 
    // int minPathSum(vector<vector<int>>& grid) {
    //     if(grid.size() == 0||grid[0].size() == 0) return 0;
    //     int rows = grid.size(),cols = grid[0].size();
    //     vector<int> dp(cols,0);
    //     dp[0] = grid[0][0];
    //     for(int i =1;i<rows;i++){
    //         for(int j = 1;j<cols;j++){
    //             if(i = 0&&j == 0){
    //                 continue;
    //             }else if(i == 0){
    //                 dp[j] = dp[j-1]+grid[i][j];
    //             }else if(j == 0){
    //                 dp[j] += grid[i][j];
    //             }else{
    //                 dp[j] = min(dp[j],dp[j-1])+grid[i][j];
    //             }
    //         }
    //     }
    //     return dp[cols-1];
    // }
};