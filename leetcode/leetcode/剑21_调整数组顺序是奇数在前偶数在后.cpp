class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int hight = 0,low = nums.size()-1;
        while(hight<low){
            if((nums[hight]&1) != 0){
                hight++;
                continue;
            }
            if((nums[low]&1) != 1){
                low--;
                continue;
            }
            swap(nums[hight],nums[low]);
        }
        return nums;
    }
};