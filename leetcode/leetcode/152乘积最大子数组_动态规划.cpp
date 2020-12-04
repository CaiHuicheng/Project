class Solution {
public:
    int maxProduct(vector<int>& nums) {
        vector<int> maxNums(nums),minNums(nums);
        for(int i = 1;i<nums.size();i++){
            maxNums[i] = max(maxNums[i-1]*nums[i],max(nums[i],minNums[i-1]*nums[i]));
            minNums[i] = min(minNums[i-1]*nums[i],min(nums[i],maxNums[i-1]*nums[i]));
        }
        return *max_element(maxNums.begin(),maxNums.end());
    }
};