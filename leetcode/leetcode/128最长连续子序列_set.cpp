class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s;
        for(auto num:nums){
            s.insert(num);
        }
        int ans = 0;
        for(const int&c:s){
            if(!s.count(c-1)){
                int cur = c;
                int curS = 1;
                while(s.count(cur+1)){
                cur += 1;
                curS += 1;
                }
                ans = max(ans,curS);
            }
        }
        return ans;
    }
};