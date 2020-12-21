class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> vis(26),nums(26);
        for(auto c:s){
            nums[c-'a']++;
        }
        string stk;
        for(auto c:s){
            if(!vis[c-'a']){
                while(!stk.empty()&&stk.back()>c){
                    if(nums[stk.back()-'a']>0){
                        vis[stk.back()-'a'] =0;
                        stk.pop_back();
                    }else{
                        break;
                    }
                }
                vis[c-'a'] = 1;
                stk.push_back(c);
            }
            nums[c-'a'] -= 1;
        }
        return stk;
    }
};