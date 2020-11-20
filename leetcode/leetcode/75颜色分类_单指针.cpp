class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int ptr = 0;
        for(int i = 0;i<n;i++){
            if(nums[i] == 0){
                swap(nums[i],nums[ptr]);
                ptr++;
            }
        }
        for(int j=0;j<n;j++){
            if(nums[j] == 1){
                swap(nums[j],nums[ptr]);
                ptr++;
            }
        }
    }
};