class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        radixSort(nums,n);
        int res = 0;
        for(int i =1 ;i<n;i++){
            res = max(res,nums[i]-nums[i-1]);
        }
        return res;
    }
private:
    //基数排序
    void radixSort(vector<int>&nums,int n){
        if(n<2) return;
        int exp = 1;
        vector<int> buf(n);
        int maxVal = *max_element(nums.begin(),nums.end());
        while(maxVal>=exp){
            vector<int> cnt(10);
            for(int i =0;i<n;i++){
                int digit = (nums[i]/exp)%10;
                cnt[digit]++;
            }
            for(int i =1;i<10;i++){
                cnt[i] +=cnt[i-1];
            }
            for(int i = n-1;i>=0;i--){
                int digit = (nums[i]/exp)%10;
                buf[cnt[digit]-1] = nums[i];
                cnt[digit]--;
            }
            copy(buf.begin(),buf.end(),nums.begin());
            exp *=10;
        }

    }
};