class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size()==0||nums2.size()==0) return {};
        if(nums1.size()<nums2.size()){
            intersection(nums2,nums1);
        }
        unordered_set<int> nums,num_s;
        vector<int> res;
        for(auto num:nums1){
            nums.insert(num);
        }
        for(auto num:nums2){
            num_s.insert(num);
        }
        for(auto num:num_s){
            if(nums.count(num)){
                res.push_back(num);
            }
        }
        return res;
    }
};