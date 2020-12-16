class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        if(nums.size() == 0) return ;
        int l = 0,r = 0;
        while(r<nums.size()){
            if(nums[r]){
                swap(nums[l],nums[r]);
                l++;
            }
            r++;
        }
    }
};