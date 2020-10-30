class Solution {
public:
    string minNumber(vector<int>& nums) {
        // 选取使字符串组合更小的排序规则
        auto compare = [](string sa, string sb){return sa+sb < sb+sa;};
        vector<string> tmp;
        for(int n : nums){
            tmp.push_back(to_string(n));
        }
        sort(tmp.begin(), tmp.end(), compare);
        string ans = "";
        for(string s : tmp) ans += s;
        return ans;
    }
};