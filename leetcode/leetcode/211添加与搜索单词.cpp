class WordDictionary {
public:
    bool isEnd;
    WordDictionary* next[26];
    /** Initialize your data structure here. */
    WordDictionary() {
        isEnd = false;
        memset(next, 0, sizeof(next));
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        WordDictionary* p = this;
        for(auto c : word) {
            if(p->next[c-'a'] == nullptr) 
                p->next[c-'a'] = new WordDictionary();
            p = p->next[c-'a'];
        }
        p->isEnd = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchWord(this, word);
    }
    bool searchWord(WordDictionary* node, string word) {
        if(word.size()==1) {  //边界
            if(isalpha(word[0])) {
                if(node->next[word[0]-'a'] && node->next[word[0]-'a']->isEnd)
                    return true;
                return false;
            }
            else {
                for(int i=0; i<26; i++)
                    if(node->next[i] && node->next[i]->isEnd)
                        return true;
                return false;
            }
        }
        else {
            if(isalpha(word[0])) {
                if(node->next[word[0]-'a'])
                    return searchWord(node->next[word[0]-'a'], word.substr(1, word.size()-1));
                else
                    return false;
            }
            else {
                bool b;
                for(int i=0; i<26; i++) {      
                    if(node->next[i]){
                        b = searchWord(node->next[i], word.substr(1, word.size()-1));
                        if(b)   return true;
                    }
                }
                return false;
            }
        }
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */