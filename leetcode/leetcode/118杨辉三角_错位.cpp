class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows, vector<int>());
        for(int i = 0; i < numRows; i++)
            for(int j = i; j < numRows; j++)
                res[j].push_back(res[j].size() > 0 && j > res[j].size() ? res[j-1][res[j].size()-1]+res[j-1][res[j].size()] : 1);
        return res;
    }
};