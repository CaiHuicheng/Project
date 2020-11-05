class Solution {
public:
    int longestValidParentheses(string s) {
        int Max = 0;
        // stack<char> st;
        // for(auto c:s){
        //     if(c == '(') st.push(c);
        //     else if(!st.empty()&&c == ')'){
        //         st.pop();
        //         Max++;
        //     }else{
        //         continue;
        //     }
        // }
        // return Max*2;
        stack<int> st;
        st.push(-1);
        for(int i = 0 ;i<s.length();i++){
            if(s.at(i) == '(')st.push(i);
            else{
                st.pop();
                if(st.empty()){
                    st.push(i);
                }else{
                    Max = max(Max,i-st.top());
                }
            }
        }
        return Max;
    }
};