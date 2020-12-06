class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int,int> counts;
        int res,nCount = 0;
        for(auto num:nums){
            ++counts[num];
            if(counts[num]>nCount){
                res = num;
                nCount = counts[num];
            }
        }
        return res;
    }
};