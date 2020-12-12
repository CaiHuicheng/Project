class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if(n<2)return n;
        int prev = nums[1]-nums[0];
        int ret = prev!=0?2:1;
        for(int i = 2;i<n;i++){
            int curr = nums[i]-nums[i-1];
            if((curr>0&&prev<=0)||(curr<0&&prev>=0)){
                ret++;
                prev = curr;
            }
        }
        return ret;
    }
};