struct tire_node{
    struct tire_node *nodes[27];
    bool is_leaf;
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        queue<int> q;
        int index;
        init_tire(wordDict);
        q.push(0);
        while(!q.empty()){
            index = q.front();
            if(index == s.length()) return true;
            q.pop();
            find(&tire,s,index,s.length(),q);
        }
        return false;
    }

private:
    struct tire_node tire;
    bool hs[2000] = {0};
    void find(struct tire_node*node,string word,int index,int len,queue<int>& q){
        int pos;
        if(node == NULL||index>=len) return;
        pos = word[index]-'a';
        if(node->nodes[pos] == NULL){
            if(!hs[index]+1){
                hs[index+1] = true;
                q.push(index+1);
            }
        }
        find(node->nodes[pos],word,index+1,len,q);
    }
    void insert(string word, int len, int idx, struct tire_node *node)
    {   
        int pos;

        if (node == NULL) {
            return;
        }

        if (idx >= len) {
            node->is_leaf = true;
            return;
        }

        pos = word[idx] - 'a';
        if (node->nodes[pos] == NULL) {
            node->nodes[pos] = (struct tire_node *)calloc(1, sizeof(struct tire_node));
        }

        insert(word, len, idx + 1, node->nodes[pos]);
    }
    void init_tire(vector<string> &words) 
    {
        int i;

        for (i = 0; i < words.size(); i++) {
            insert(words[i], words[i].length(), 0, &tire);
        }
    }

};