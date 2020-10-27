class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        // map<int,int> map;
        // for(auto num:nums){
        //     if(++map[num] > 1) return num;
        // }
        // return -1;
        sort(nums.begin(),nums.end());
        for(int i = 0 ;i < nums.size();++i){
            if(nums[i] == nums[i+1])return nums[i];
        }
        return -1;
    }
};