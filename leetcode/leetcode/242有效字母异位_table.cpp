class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size()!=t.size()) return 0;
        vector<int> table(26,0);
        for(auto c:s){
            table[c-'a']++;
        }
        for(int i = 0;i<t.size();i++){
            table[t[i]-'a']--;
            if(table[t[i]-'a']<0) return false;
        }
        return true;
    }
};