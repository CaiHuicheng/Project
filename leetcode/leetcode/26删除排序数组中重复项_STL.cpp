class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        auto end_unique=unique(nums.begin(),nums.end());
        nums.erase(end_unique,nums.end());
        return nums.size();
    }
};