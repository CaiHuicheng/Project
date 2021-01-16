class Solution {
public:
    void dfs(int x, vector<vector<int>> &edge, vector<int> &vis) {
        vis[x] = true;
        for (auto &y : edge[x]) {
            if (!vis[y]) {
                dfs(y, edge, vis);
            }
        }
    }

    int removeStones(vector<vector<int>> &stones) {
        int n = stones.size();
        vector<vector<int>> edge(n);
        unordered_map<int, vector<int>> rec;
        for (int i = 0; i < n; i++) {
            rec[stones[i][0]].push_back(i);
            rec[stones[i][1] + 10001].push_back(i);
        }
        for (auto &[_, vec] : rec) {
            int k = vec.size();
            for (int i = 1; i < k; i++) {
                edge[vec[i - 1]].push_back(vec[i]);
                edge[vec[i]].push_back(vec[i - 1]);
            }
        }

        vector<int> vis(n);
        int num = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                num++;
                dfs(i, edge, vis);
            }
        }
        return n - num;
    }
};