/*
序列	子集	0/1 序列对应的二进制数
000	    {}	        0
001     {9}	        1
010	    {2}         2
011	    {2,9}       3
100	    {5}         4
101	    {5,9}       5
110	    {5,2}       6
111	    {5,2,9}     7
*/

class Solution {
public:
    vector<int> t;
    vector<vector<int>>ans;
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        for(int mask = 0;mask<(1<<n);++mask){
            t.clear();
            for(int i = 0;i<n;++i){
                if(mask&(1<<i)){
                    t.push_back(nums[i]);
                }
            }
            ans.push_back(t);
        }
        return ans;
    }
};
