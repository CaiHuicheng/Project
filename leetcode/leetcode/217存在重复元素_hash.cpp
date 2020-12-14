class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> check;
        for(auto num:nums){
            if(check.find(num) != check.end()){
                return true;
            }
            check.insert(num);
        }
        return false;
    }
};