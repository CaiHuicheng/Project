class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return 1;
        int res = 0;
        int ans = 0;
        Sort(nums,0,nums.size()-1);
        for(int i = 1;i<nums.size();i++){
            if(nums[i-1] == nums[i]) continue;
            else if(nums[i-1]+1 == nums[i]) ans++;
            else{
                res = max(res,ans);
                ans = 0;
            }
            res = max(res,ans);
        }
        return res+1;
    }
    void Sort(vector<int>& nums,int left,int right){
        if(left>right) return;
        int l = left,r = right;
        int mid = nums[l];
        while(l<r){
            while(l<r&&nums[r]>=mid) r--;
            nums[l] = nums[r];
            while(l<r&&nums[l]<mid) l++;
            nums[r] = nums[l]; 
        }
        nums[l] = mid;
        Sort(nums,left,l-1);
        Sort(nums,l+1,right);
    }
};