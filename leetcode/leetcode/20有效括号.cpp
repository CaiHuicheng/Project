class Solution {
public:
    bool isValid(string s) {
        if(s.size()%2 == 1||s.length()==0) return false;
        unordered_map<char,char> strMap{
            {'(',')'},
            {'{','}'},
            {'[',']'}
        };
        stack<char> stk;
        for(auto c:s){
           if(strMap.find(c)!=strMap.end()) stk.push(c);
           else{
               if(stk.empty()) return false;
               else{
                   if(strMap[stk.top()] == c) stk.pop();
                   else return false;
               }
           }
        }
        return stk.empty();

    }
};
