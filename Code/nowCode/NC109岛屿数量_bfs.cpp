class Solution {
public:
    /**
     * 判断岛屿数量
     * @param grid char字符型vector<vector<>> 
     * @return int整型
     */
    int solve(vector<vector<char> >& grid) {
        //看成无限图，用dfs或bfs
        int nr = grid.size();
        if(!nr) return 0;
        int nc = grid[0].size();
        int nums =0;
        for(int i=0;i<nr;++i){
            for(int j = 0;j<nc;++j){
                if(grid[i][j] == '1'){
                    ++nums;
                    grid[i][j] = '0';
                    queue<pair<int, int>> dp;
                    dp.push({i,j});
                    while(!dp.empty()){
                        auto rc = dp.front();
                        dp.pop();
                        int r = rc.first;
                        int c = rc.second;
                        if(r-1>=0&&grid[r-1][c] == '1'){
                            dp.push({r-1,c});
                            grid[r-1][c] = '0';
                        }
                        if(r+1<nr&&grid[r+1][c] == '1'){
                            dp.push({r+1,c});
                            grid[r+1][c] = '0';
                        }
                        if(c-1>=0&&grid[r][c-1] == '1'){
                            dp.push({r,c-1});
                            grid[r][c-1] = '0';
                        }
                        if(c+1<nc&&grid[r][c+1] == '1'){
                            dp.push({r,c+1});
                            grid[r][c+1] ='0';
                        }
                    }
                }
                
            }
        }
        return nums;
    }
};