class Solution {
public:
    string minWindow(string s, string t) {
        int count[128] = {0};
        for(auto c:t) ++count[c];
        int len = 0,minlen = s.length();
        string res;
        for(int slow = 0,high = 0;high<s.length();++high){
            count[s[high]]--;
            if(count[s[high]]>=0) len++;
            while(len == t.length()){
                if(high-slow+1<=minlen){
                    minlen = high-slow+1;
                    res = s.substr(slow,high-slow+1);
                }
                count[s[slow]]++;
                if(count[s[slow]]>0) --len;
                ++slow;
            }
        }
        return res;
    }
};