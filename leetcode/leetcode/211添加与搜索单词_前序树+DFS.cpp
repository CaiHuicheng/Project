struct TrieNode
{
    bool end;
    unordered_map<char, TrieNode*> map;
    TrieNode() : end(false) {}
};


class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        m_root = new TrieNode;
    }

    /** Adds a word into the data structure. */
    void addWord(string word) {

        if (word.empty())
        {
            return;
        }

        TrieNode* cur = m_root;

        for (int i = 0; i < word.size(); ++i)
        {
            auto iter = cur->map.find(word.at(i));
            if (iter == cur->map.end())
            {
                cur->map[word.at(i)] = new TrieNode;
            }
            cur = cur->map[word.at(i)];
        }

        cur->end = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {

        if (word.empty())
        {
            return false;
        }

        bool res = false;
        dfs(m_root, word, 0, res);

        return res;
    }

    void dfs(TrieNode* node, const string& word, int index, bool& res)
    {
        if (index == word.size())
        {
            if(node->end)
            {
                res = true;
            }
                
            return;
        }

        if (word.at(index) == '.')
        {
            for (const auto& p : node->map)
            {
                dfs(p.second, word, index + 1, res);
            }
        }
        else
        {
            auto iter = node->map.find(word.at(index));
            if (iter != node->map.end())
            {
                dfs(iter->second, word, index + 1, res);
            }
        }
    }

private:
    TrieNode* m_root;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */