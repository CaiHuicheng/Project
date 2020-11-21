class Solution {
public:
    vector<int> t;
    vector<vector<int>>ans;
    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(nums,0);
        return ans;
    }
    void dfs(vector<int>& nums,int tail){
        if(tail == nums.size()){
            ans.push_back(t);
            return;
        }
        t.push_back(nums[tail]);
        dfs(nums,tail+1);
        t.pop_back();
        dfs(nums,tail+1);
    }
};