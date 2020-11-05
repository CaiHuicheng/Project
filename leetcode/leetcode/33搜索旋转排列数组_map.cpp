class Solution {
public:
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        unordered_map<int,int> map;
        for(int i = 0 ;i<size;i++){
            map.insert(std::pair<int,int>(nums[i],i));
        }
        if(map.count(target)){
            return map[target];
        }else{
            return -1;
        }
    }
};