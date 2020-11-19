class WordDictionary {
public:
    /** Initialize your data structure here. */
    struct node{
        bool isEnd;
        unordered_map<char,node*>children;
        node(){isEnd=false;}
        
    };
    node* root;
    WordDictionary() {
        root=new node();
    }
    /** Adds a word into the data structure. */
    void addWord(string word) {
        auto p=root;
        for(auto c:word){
            if(!p->children.count(c))p->children.insert({c,new node()});
            p=p->children[c];
        }
        p->isEnd=true;
    } 
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        auto p=root;
        return help(p,word.begin(),word.end());
    }
    template<typename it>
    bool help(node* root,it l,it r){
        if(l==r)return root->isEnd;
        if(*l=='.')
            for(auto t:root->children)
                if(help(t.second,l+1,r))return true;
        if(root->children.count(*l))return help(root->children[*l],l+1,r);
        return false;  
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */