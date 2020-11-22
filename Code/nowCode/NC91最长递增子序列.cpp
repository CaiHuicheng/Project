class Solution {
public:
    /**
     * retrun the longest increasing subsequence
     * @param arr int整型vector the array
     * @return int整型vector
     */
    vector<int> LIS(vector<int>& arr) {
        // write code here
        if(arr.size() <= 1) return arr;
        vector<int> dp(arr.size(),0);
        vector<int> pp(arr.size(),0);
        int len = 0;dp[len] = arr[0];
        for(int i=0;i<arr.size();i++){
            if(arr[i]>dp[len]){
                dp[++len] = arr[i];
                pp[i] = len; 
            }else{
                int slow = 0,high = len;
                while(slow<=high){
                    int mid = (slow+high)/2;
                    if(dp[mid] < arr[i]){
                        slow = mid+1;
                    }else high = mid -1;
                }
                if(slow!=-1){
                    dp[slow] = arr[i];
                    pp[i] = slow;
                }else{
                    dp[0] = arr[i];
                    pp[i] = 0;
                }
            }
        }
        vector<int> res(len+1,INT_MAX);
        for(int i = arr.size()-1;i>=0;i--){
            if(pp[i] == len){
                res[len] = min(res[len],arr[i]);
                len --;
            }
        }
        return res;
    }
};