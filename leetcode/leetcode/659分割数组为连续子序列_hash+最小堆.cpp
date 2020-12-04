class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int,priority_queue<int,vector<int>,greater<int>>> mp;
        for(auto num:nums){
            if(mp.find(num) == mp.end()){
                mp[num] = priority_queue<int,vector<int>,greater<int>>();
            }
            if(mp.find(num-1)!=mp.end()){
                int prevLength  = mp[num-1].top();
                mp[num-1].pop();
                if(mp[num-1].empty()){
                    mp.erase(num-1);
                }
                mp[num].push(prevLength+1);
            }else{
                mp[num].push(1);
            }
        }
        for(auto it = mp.begin();it!=mp.end();++it){
            priority_queue<int, vector<int>,greater<int>> queue = it->second;
            if (queue.top() < 3) {
                return false;
            }
        }
        return true;
    }
};