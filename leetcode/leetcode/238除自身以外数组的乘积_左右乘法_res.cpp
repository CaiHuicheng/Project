class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        res[0] = 1;
        for(int i = 1;i<n;i++){
            res[i] = nums[i-1]*res[i-1];
        }
        int R = 1;
        for(int i = n-1;i>=0;i--){
            res[i] = res[i]*R;
            R *= nums[i];
        }
        return res;
    }
};