class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<string,char> str2ch;
        unordered_map<char,string>ch2str;
        int m = s.length();
        int i = 0;
        for(auto ch:pattern){
            if(i>=m) return false;
            int j = i;
            while(j<m&&s[j] != ' ') j++;
            const string &tmp = s.substr(i,j-i);
            if(str2ch.count(tmp)&&str2ch[tmp]!=ch){
                return false;
            }
            if(ch2str.count(ch)&&ch2str[ch]!=tmp){
                return false;
            }
            str2ch[tmp] = ch;
            ch2str[ch] = tmp;
            i = j+1;
        } 
        return  i>=m;
    }
};