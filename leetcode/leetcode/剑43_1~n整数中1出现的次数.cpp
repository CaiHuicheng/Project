class Solution {
public:
    int countDigitOne(int n) {
        // if(!n) return 0;
        // std::vector<int> nums;
        // int res;
        // while(n){
        //     nums.push_back(n%10);
        //     n = n/10;
        // }
        // for(int i = nums.size()-1;i>=0;--i){
        //     auto left = 0,right = 0,t = 1;
        //     for(int j = nums.size()-1;j>i;--j){
        //         left = left*10+nums[j];
        //     }
        //     for(int j = i-1;j>=0;--j){
        //             right = right*10+nums[j];
        //             t = t*10;
        //     }   
        //     res+=left*t;
        //     if(nums[i]>1)res+=t;
        //     if(nums[i]==1)res+=right+1;
        // }
        // return res;
        int res = 0;
        long long i = 0;
        for(i = 1;i<n;i*=10){
            int a = n/i,b = n%i;
            res+=((a+8)/10*i+(a%10==1)*(b+1));
        }
        if(i == n){
                res+=1;
            }
        return res;
    }
};
