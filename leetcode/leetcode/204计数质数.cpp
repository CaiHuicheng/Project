class Solution {
public:
    int isPrimes(int n){
        for(int i = 2;i*i<=n;i++){
            if(n%i == 0){
                return false;
            }
        }
        return true;
    }
    int countPrimes(int n) {
        int ans =0;
        for(int i = 2;i<n;i++){
            ans+=isPrimes(i);
        }
        return ans;
    }
};