class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
       int ans = 0;
       vector<int> st;
       heights.insert(heights.begin(),0);
       heights.push_back(0);
       for(int i = 0;i<heights.size();i++){
           while(!st.empty()&&heights[st.back()]>heights[i]){
               int tail = st.back();
               st.pop_back();
               int left = st.back()+1;
               int right = i - 1;
               ans = max(ans,(right-left+1)*heights[tail]);
           }
           st.push_back(i);
       }
       return ans;
    }
};