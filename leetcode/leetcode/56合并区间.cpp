class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() == 0) return {};
        sort(intervals.begin(),intervals.end());
        vector<vector<int>> res;
        for(auto &i:intervals){
            if(res.empty()||i[0]>res.back()[1]) res.push_back(i);
            else
                res.back()[1] =  max(i[1],res.back()[1]);
        }
        return res;
    }
};