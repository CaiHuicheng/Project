class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n<2) return 0;
        // radixSort(nums,n);
        // int res = 0;
        // for(int i =1 ;i<n;i++){
        //     res = max(res,nums[i]-nums[i-1]);
        // }
        int res = bucketSort(nums,n);
        return res;
    }
private:
    //基数排序
    void radixSort(vector<int>&nums,int n){
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

    int bucketSort(vector<int>&nums,int n){
        int maxVal = *max_element(nums.begin(),nums.end());
        int minVal = *min_element(nums.begin(),nums.end());
        int d = max(1,-(maxVal-minVal)/(n-1));
        int bucketSize = (maxVal-minVal)/d+1;
        vector<pair<int,int>> bucket(bucketSize,{-1,-1});
        for(int i = 0;i<n;i++){
            int index = (nums[i]-minVal)/d;
            if(bucket[index].first == -1){
                bucket[index].first = bucket[index].second = nums[i];
            }else{
                bucket[index].first = min(bucket[index].first,nums[i]);
                bucket[index].second = max(bucket[index].second,nums[i]);
            }
        }
        int res = 0;
        int prev  =-1;
        for(int i = 0;i<bucketSize;i++){
            if(bucket[i].first == -1) continue;
            if(prev != -1){
                res = max(res,bucket[i].first-bucket[prev].second);
            }
            prev = i;
        }
        return res;
    }
};