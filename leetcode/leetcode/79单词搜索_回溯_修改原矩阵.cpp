class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(word.empty())    return false;
        for(int i = 0; i < board.size(); ++i)
            for(int j = 0; j < board[0].size(); ++j)
                if(dfs(board, word, i, j, 0))   return true;    //找到目标路径
        return false;
    }
    bool dfs(vector<vector<char>>& board, string &word,int i,int j,int w) {
        if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[w])
            return false;   
        if(w == word.size()-1)      //路径长度等于目标路径   
            return true;
        board[i][j] = '\0';         //标记当前路径走过
        bool res = ( dfs(board,word,i-1,j,w+1) || dfs(board,word,i+1,j,w+1)
        || dfs(board,word,i,j-1,w+1) || dfs(board,word,i,j+1,w+1) );    //判断接下来的路径是否正确
        board[i][j] = word[w];      //还原字符
        return res;
    }
};