class Solution {
public:
    vector<int> topologicalSort(vector<vector<int>> &Adj, vector<int> &Indegree, int n){
        vector<int> res;
        queue<int> q;
        for(int i = 0;i<n;i++){
            if(Indegree[i]==0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int front = q.front();
            q.pop();
            res.push_back(front);
            for(int successor: Adj[front]){
                Indegree[successor]--;
                if(Indegree[successor]==0){
                    q.push(successor);
                }
            }
        }
        if(res.size()==n){return res;}
        return vector<int>();
    }
    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
        // 第 1 步：数据预处理，给没有归属于一个组的项目编上组号
        for(int i=0;i<group.size();i++){
            if(group[i] == -1){
                group[i] = m;
                m++;
            }
        }
        // 第 2 步：实例化组和项目的邻接表
        vector<vector<int>> groupAdj(m, vector<int>());
        vector<vector<int>> itemAdj(n, vector<int>());

        // 第 3 步：建图和统计入度数组
        vector<int> groupsIndegree(m, 0);
        vector<int> itemIndegree(n, 0);

        int len = group.size();
        for(int i=0;i<len;i++){
            int currentGroup = group[i];
            for(int beforeItem: beforeItems[i]){
                int beforeGroup = group[beforeItem];
                if(beforeGroup!=currentGroup){
                    groupAdj[beforeGroup].push_back(currentGroup);
                    groupsIndegree[currentGroup]++;
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int item: beforeItems[i]){
                itemAdj[item].push_back(i);
                itemIndegree[i]++;
            }
        }
        // 第 4 步：得到组和项目的拓扑排序结果
        vector<int> groupList = topologicalSort(groupAdj, groupsIndegree, m);
        if(groupList.size()==0){
            return vector<int> ();
        }
        vector<int> itemList = topologicalSort(itemAdj, itemIndegree, n);
        if(itemList.size()==0){
            return vector<int> ();
        }
        // 第 5 步：根据项目的拓扑排序结果，项目到组的多对一关系，建立组到项目的一对多关系
        // key：组，value：在同一组的项目列表
        map<int, vector<int>> group2Items;
        for(int item: itemList){
            group2Items[group[item]].push_back(item);
        }
        // 第 6 步：把组的拓扑排序结果替换成为项目的拓扑排序结果
        vector<int> res;
        for(int groupId: groupList){
            vector<int> items = group2Items[groupId];
            for(int item: items){
                res.push_back(item);
            }
        }
        return res;
    } 
};