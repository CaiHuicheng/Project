class Solution {
private:
    vector<string> res;
public:
    vector<string> generateParenthesis(int n) {
        if(n<=0) return res;
        dfs("",n,0,0);
        return res;
    }

    // void getParenthesis(string str,int left,int right){
    //     if(left == 0 && right ==0 ) res.push_back(str);
    //     if(left == right){
    //         getParenthesis(str+"(",left-1,right);
    //     }else if(left<right){
    //         if(left>0){
    //             getParenthesis(str+"(",left,right-1);
    //         }
    //         getParenthesis(str+")",left,right-1);
    //     }
    // }
    void dfs(string path,int n,int left,int right){
        if(right>left||left>n||right>n) return;
        if(right == left && left == n){
            res.push_back(path);
        }
        dfs(path+'(',n,left+1,right);
        dfs(path+')',n,left,right+1);
    }

};