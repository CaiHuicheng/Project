class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n),right(n);
        stack<int> ms;
        for(int i=0;i<n;++i){
            while(!ms.empty()&&heights[ms.top()]>=heights[i]){
                ms.pop();
            }
            left[i] = (ms.empty()?-1:ms.top());
            ms.push(i);
        }
        ms = stack<int>();
        for(int i = n-1;i>=0;--i){
            while(!ms.empty()&&heights[ms.top()]>=heights[i]){
                ms.pop();
            }
            right[i] = (ms.empty()?n:ms.top());
            ms.push(i);
        }
        int ans = 0;
        for(int i = 0;i<n;++i){
            ans = max(ans,(right[i]-left[i]-1)*heights[i]);
        }
        return ans;
    }
};