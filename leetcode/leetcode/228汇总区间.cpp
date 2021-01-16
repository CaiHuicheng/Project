class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if(nums.empty()) return {};
        vector<string> ret;
        // i为起始位置，j为终止位置
        int i = 0, j = 1;
        while(j < nums.size()){
            if(nums[j] == nums[j - 1] + 1){
                // 如果满足条件，需要将终止位置后移
                j++;
            }
            else{
                // 如果区间只有一个数
                if(j == i + 1){
                    ret.push_back(to_string(nums[i]));
                    j++;
                    i++; // 更新起始位置
                }
                // 如果区间不止一个数
                else{
                    ret.push_back(to_string(nums[i]) + "->" + to_string(nums[j - 1]));
                    i = j; // 更新起始位置
                    j++;
                }
            }
        }
        // 最后一个区间
        if(i == j - 1) ret.push_back(to_string(nums[i]));
        if(i != j - 1) ret.push_back(to_string(nums[i]) + "->" + to_string(nums[j - 1])); // 直接else也行
        return ret;
    }
};
