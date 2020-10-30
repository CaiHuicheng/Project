class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // unordered_set<int> arrays;
        // for(auto num:nums){
        //     if(arrays.count(target-num)) return vector<int>{num,target-num};
        //     arrays.insert(num);
        // }
        // return vector<int> {-1,-1};
        for(int i=0;i<nums.size();++i){
            if(binary_search(nums.begin()+i+1,nums.end(),target - nums[i])){
                return vector<int>{nums[i],target - nums[i]};
            }
        }
        return vector<int>{-1,-1};
    }
};