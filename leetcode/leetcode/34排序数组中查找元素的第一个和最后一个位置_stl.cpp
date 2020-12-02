class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto [l, r] = equal_range(nums.begin(), nums.end(), target);
        if (l == r) return {-1, -1};
        else    return {(int)(l-nums.begin()), (int)(r-nums.begin()-1)};
    }
};