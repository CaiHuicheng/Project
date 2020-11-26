class Solution {
public:
    //UNICODE字符 字符离散未知 用map映射
    bool isAnagram(string s, string t) {
        if(s.size()!=t.size()) return 0;
        unordered_map<char,int> table;
        for(auto c:s){
            table[c]++;
        }
        for(auto c:t){
            table[c]--;
            if(table[c]<0) return false;
        }
        return true;
    }
};