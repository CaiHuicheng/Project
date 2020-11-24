struct TrieNode
{
    bool end;
    vector<TrieNode*> map;

    TrieNode() : end(false), map(26, nullptr) {}
};


class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        m_root = new TrieNode;
    }

    /** Inserts a word into the trie. */
    void insert(string word) {

        TrieNode* cur = m_root;

        for (int i = 0; i < word.size(); ++i)
        {
            TrieNode*& next = cur->map.at(word.at(i) - 'a');
            if (next == nullptr)
            {
                next = new TrieNode;
            }

            cur = next;
        }

        cur->end = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {

        TrieNode* cur = m_root;

        for (int i = 0; i < word.size(); ++i)
        {
            TrieNode*& next = cur->map.at(word.at(i) - 'a');
            if (next == nullptr)
            {
                return false;
            }

            cur = next;
        }
        
        return cur->end;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {

        TrieNode* cur = m_root;

        for (int i = 0; i < prefix.size(); ++i)
        {
            TrieNode*& next = cur->map.at(prefix.at(i) - 'a');
            if (next == nullptr)
            {
                return false;
            }

            cur = next;
        }

        return true;
    }


private:
    TrieNode* m_root;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */