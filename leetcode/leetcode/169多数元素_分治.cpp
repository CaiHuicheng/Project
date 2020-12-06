class Solution {
    int count_in_range(vector<int>& nums, int target, int lo, int hi) {
        int count = 0;
        for (int i = lo; i <= hi; ++i)
            if (nums[i] == target)
                ++count;
        return count;
    }
    int majority_element_rec(vector<int>& nums, int lo, int hi) {
        if (lo == hi)
            return nums[lo];
        int mid = (lo + hi) / 2;
        int left_majority = majority_element_rec(nums, lo, mid);
        int right_majority = majority_element_rec(nums, mid + 1, hi);
        if (count_in_range(nums, left_majority, lo, hi) > (hi - lo + 1) / 2)
            return left_majority;
        if (count_in_range(nums, right_majority, lo, hi) > (hi - lo + 1) / 2)
            return right_majority;
        return -1;
    }
public:
    int majorityElement(vector<int>& nums) {
        return majority_element_rec(nums, 0, nums.size() - 1);
    }
};