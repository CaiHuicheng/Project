class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        dp = vector<int>(s.size(),0);
        root = new TrieNode();
        auto node = root;
        for(auto word: wordDict){
            node = root;
            for(auto c:word){
                if(node->next.count(c) == 0){
                    node->next[c] = new TrieNode();
                }
                node =node->next[c];
            }
            node->flag = true;
        }
        return func(s,0,s.size());
    }

private:
    struct TrieNode{
        bool flag;
        map<char,TrieNode*> next;
        TrieNode():flag(false){}
    };
    TrieNode *root;
    vector<int> dp;
    bool func(string& s,int start,int end){
        if(start == end) return true;
        if(dp[start]!=0) return dp[start]>0;
        auto node = root;
        for(int i = start;i<end;++i){
            if(node->next.count(s[i]) == 0)break;
            node = node->next[s[i]];
            if(node->flag&&func(s,i+1,end)){
                dp[start] = 1;
                return true;
            }
        }
        dp[start] = -1;
        return false;
    }
};