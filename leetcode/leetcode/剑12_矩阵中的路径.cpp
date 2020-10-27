// class Solution {
// public:
    // bool exist(vector<vector<char>>& board, string word) {
        // if(board.size()==0) return false;
        // for(int i=0;i<board.size();++i){
           // for(int j=0;j<board[0].size();++j){
               // if(dfs(board,word,i,j,0)) return true;
           // } 
        // }
        // return false;
    // }

    // bool dfs(vector<vector<char>>& board,string word,int i,int j,int lenght){
        // if(i>=board.size()||j>=board[0].size()||i<0||j<0||lenght>word.size()||word[lenght] !=board[i][j]) return false;
        // if(lenght == word.size()-1&&word[lenght] == board[i][j]){
            // return true;
        // }
        // char temp = board[i][j];
        // board[i][j] = '0';
        // bool flag = dfs(board,word,i,j+1,lenght+1)||dfs(board,word,i,j-1,lenght+1)||dfs(board,word,i+1,j,lenght+1)||dfs(board,word,i-1,j,lenght+1);
        // board[i][j] = temp;
        // return flag;
    // }
// };
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(word.empty()) return false;
        for(int i=0;i<board.size();++i){
           for(int j=0;j<board[0].size();++j){
               if(dfs(board,word,i,j,0)) return true;
           } 
        }
        return false;
    }

    bool dfs(vector<vector<char>>& board,string &word,int i,int j,int lenght){
        if(i>=board.size()||j>=board[0].size()||i<0||j<0||word[lenght] !=board[i][j]) return false;
        if(lenght == word.size()-1){
            return true;
        }
        board[i][j] = '\0';
        bool flag = dfs(board,word,i-1,j,lenght+1)||dfs(board,word,i+1,j,lenght+1)||dfs(board,word,i,j-1,lenght+1)||dfs(board,word,i,j+1,lenght+1);
        board[i][j] = word[lenght];
        return flag;
    }
};