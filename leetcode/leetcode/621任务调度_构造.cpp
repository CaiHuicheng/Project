class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char,int> mp;
        for(char c:tasks){
            ++mp[c];
        }
        int maxExec = max_element(mp.begin(),mp.end(),[](const auto& u,const auto& v){
            return u.second<v.second;
        })->second;
        int maxCount = accumulate(mp.begin(),mp.end(),0,[=](int acc,const auto& u){
            return acc+=(u.second == maxExec);
        });
        return max((maxExec-1)*(n+1)+maxCount,static_cast<int>(tasks.size()));
    }
};