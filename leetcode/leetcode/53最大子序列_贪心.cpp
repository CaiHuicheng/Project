class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int p = 0, maxNum = nums[0];
        for(const auto &num:nums){
            p =p+num;
            maxNum = max(maxNum,p);
            if(p<0){
                p = 0;
            }
        }
        return maxNum;
    }
};