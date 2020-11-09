class Solution {
public:
    void backtrack(vector<string>& res,string str,int first,int len){
        bool flag = false;
        if(first == len){
            if(res.empty()) res.push_back(str);
            else{
                for(auto n:res){
                    if(n == str){
                        flag = true;
                        continue;
                    }
                }
                if(!flag) res.push_back(str);
            }
            return;
        }
        for(int i = first;i<len;i++){
            swap(str[i], str[first]);
            backtrack(res,str,first+1,len);
            swap(str[i], str[first]);
        }
    }
	
    vector<string> Permutation(string str) {
        vector<string> res;
        if(str.length() == 0) return res; //输入为空
        if(str.length() == 1) {//输入一个字符的情况
            res.push_back(str);
            return res;
        }
        backtrack(res,str,0,str.length());
        return res;
    }
};