class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int ans = 0;
        //枚举左边界
        for(int i = 0;i<n;i++){
            int minHight = INT_MAX;
            //枚举右边界
            for(int j=i;j<n;j++){
                minHight = min(minHight,heights[j]);
                ans = max(ans,(j-i+1)*minHight);
            }
        }
        return ans;
    }
};