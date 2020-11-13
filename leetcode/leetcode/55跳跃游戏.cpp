class Solution {
public:
    bool canJump(vector<int>& nums) {
        int len = nums.size();
        int index = 0;
        for(int i=0;i<len;i++){
            if(i<=index){
                index = max(index,i+nums[i]);
                if(index>=len-1){
                    return true;
                }
            }
        }
        return false;
    }
};