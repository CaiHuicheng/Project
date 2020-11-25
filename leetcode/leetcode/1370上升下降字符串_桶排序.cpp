class Solution {
public:
    string sortString(string s) {
        if(s.size() == 0||s.size() == 1) return s;
        vector<int> nums(26);
        for(auto c:s){
            nums[c-'a']++;
        }
        string res;
        while(res.size()<s.size()){
            for(int i=0;i<26;i++){
                if(nums[i]){
                    res.push_back(i+'a');
                    nums[i]--;
                }
            }
            for(int i =25;i>=0;i--){
                if(nums[i]){
                    res.push_back(i+'a');
                    nums[i]--;
                }
            }
        }
        return res;
    }
};