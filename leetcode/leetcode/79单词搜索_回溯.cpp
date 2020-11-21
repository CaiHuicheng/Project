class Solution {
public:
    bool check(vector<vector<char>>& board, vector<vector<int>>& visited, int i, int j, string& s, int k){
        if(board[i][j] != s[k]){
            return false;
        }else if(k == s.length()-1){
            return true;
        }
        visited[i][j] = true;
        vector<pair<int,int>> directions{{0,1},{0,-1},{1,0},{-1,0}};
        bool result = false;
        for(const auto& dir:directions){
            int indexI = i+dir.first,indexJ = j+dir.second;
            if(indexI>=0&&indexI<board.size()&&indexJ>=0&&indexJ<board[0].size()){
                if(!visited[indexI][indexJ]){
                    bool flag = check(board,visited,indexI,indexJ,s,k+1);
                    if(flag){
                        result = true;
                        break;
                    }
                }
            }
        }
        visited[i][j] = false;
        return result;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int h = board.size(),w = board[0].size();
        vector<vector<int>> visited(h,vector<int>(w));
        for(int i = 0;i<h;i++){
            for(int j = 0;j<w;j++){
                bool flag = check(board,visited,i,j,word,0);
                if(flag){
                    return true;
                }
            }
        }
        return false;
    }
};