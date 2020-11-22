class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minN = 1e9,maxN = 0;
        for(auto price:prices){
            maxN = max(maxN,price-minN);
            minN = min(minN,price); 
        }
        return maxN;
    }
};