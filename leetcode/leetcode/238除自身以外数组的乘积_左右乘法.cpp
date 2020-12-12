class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int>L(n,0),R(n,0);
        vector<int> res(n);
        L[0] = 1;
        for(int i = 1;i<n;i++){
            L[i] = nums[i-1]*L[i-1];
        }
        R[n-1] = 1;
        for(int i = n-2;i>=0;i--){
            R[i] = nums[i+1]*R[i+1];
        }
        for(int i = 0;i<n;i++){
            res[i] = L[i]*R[i];
        }
        return res;
    }
};