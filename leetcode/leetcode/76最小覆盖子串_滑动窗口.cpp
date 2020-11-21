class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int> count;
        for(auto c:t) count[c]++;
        int len = 0,n = s.size();
        int minlen = n;
        int slow = 0,high = 0;
        string ans ="";
        for(;high<n;high++){
            count[s[high]]--;
            if(count[s[high]]>=0) len++;
            while(len == t.size()){
                if(high-slow+1<=minlen){
                    minlen = high-slow+1;
                    ans = s.substr(slow,high-slow+1);
                }
                count[s[slow]]++;
                if(count[s[slow]]>0) len--;
                slow++;
            }
        }
        return ans;
    }
};