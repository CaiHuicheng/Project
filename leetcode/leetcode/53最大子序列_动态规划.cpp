class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int p = 0, maxNum = nums[0];
        for(const auto &num:nums){
            p = max(p+num,num);
            maxNum = max(maxNum,p);
        }
        return maxNum;
    }
};