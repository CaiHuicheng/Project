// class Solution {
// public:
//     int majorityElement(vector<int>& nums) {
//         unordered_map<int,int>map;
//         int len = nums.size(),res = 0;
//         if(len == 1 || len == 2)return nums[0];
//         for(auto num:nums){
//             map[num]++;
//             if(map[num] > (len/2)){
//                 res = num;
//                 break;
//             }
//         }
//         return res;
//     }
// };
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int moleVote = 0, res = 0;
        for(auto i : nums){
            if(moleVote == 0){
                res = i;
            }
            moleVote += res == i ? 1 : -1;
        }
        return res;
    }
};