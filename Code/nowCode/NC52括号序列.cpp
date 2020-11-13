class Solution {
public:
    /**
     * 
     * @param s string字符串 
     * @return bool布尔型
     */
    bool isValid(string s) {
        // write code here
        if(s.size()%2 == 1||s.length() == 0) return false;
        map<char,char> sm{
            {'(',')'},
            {'{','}'},
            {'[',']'}
        };
        stack<char> st;
        for(auto c:s){
            if(sm.find(c)!=sm.end())st.push(c);
            else{
                if(st.empty()) return false;
                else{
                    if(sm[st.top()] == c)st.pop();
                    else return false;
                }
            }
        }
        return st.empty();
    }
};