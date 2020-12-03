class Solution {
public:
    int countPrimes(int n) {
        vector<int> Primes;
        vector<int> isPrimes(n,1);
        for(int i = 2;i<n;++i){
            if(isPrimes[i]){
                Primes.push_back(i);
            }
            for(int j = 0;j<Primes.size()&&i*Primes[j]<n;j++){
                isPrimes[i*Primes[j]] = 0;
                if(i%Primes[j] == 0){
                    break;
                }
            }
        }
        return Primes.size();
    }
};