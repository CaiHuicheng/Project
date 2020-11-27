class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int,int> countAB;
        for(auto a:A){
            for(auto b:B){
                ++countAB[a+b];
            }
        }
        int ans = 0;
        for(auto c:C){
            for(auto d:D){
                if(countAB.count(-c-d)){
                    ans += countAB[-c-d];
                }
            }
        }
        return ans;
    }
};