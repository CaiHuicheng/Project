class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int n = T.size();
        vector<int> ans(n);
        stack<int> st;
        for(int i=0;i<n;++i){
            while(!st.empty()&&T[st.top()]<T[i]){
                int indexI = st.top();
                ans [indexI] = i - indexI;
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};