class Solution {

private:
    vector<vector<int>> res;
    vector<int> temp;

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        if(candidates.size() == 0) return res;
        sort(candidates.begin(),candidates.end());
        dfs(candidates,target,0,0);
        return res;
    }

    void dfs(vector<int>& candidates,int target,int sum ,int index){
        if(sum>target) return;
        if(sum == target){
            res.push_back(temp);
            return;
        }
        for(int i = index;i<candidates.size();i++){
            if(sum+candidates[i] <= target){
                if(i>index&&candidates[i]==candidates[i-1]) continue;
                temp.push_back(candidates[i]);
                dfs(candidates,target,sum+candidates[i],i+1);
                temp.pop_back();
            }
        }
        return;
    }
};