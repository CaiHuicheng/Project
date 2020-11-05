class Solution {
public:
    int search(vector<int>& nums, int target) {
        int size = nums.size();
        // unordered_map<int,int> map;
        // for(int i = 0 ;i<size;i++){
        //     map.insert(std::pair<int,int>(nums[i],i));
        // }
        // if(map.count(target)){
        //     return map[target];
        // }else{
        //     return -1;
        // }
        if(!size) return -1;
        if(size == 1) return target == nums[size-1] ? 0:-1;
        int left = 0 ,right = size-1;
        while(left<=right){
            int mid = (left+right)/2;
            if(nums[mid] == target) return mid;
            else if(nums[left] <= nums[mid]){
                if(nums[left]<=target&&target<nums[mid]){
                    right = mid -1;
                }else{
                    left = mid + 1;
                }
            }else{
                if(nums[mid]<target&&target<=nums[right]){
                    left = mid+1;
                }else{
                    right = mid -1;
                }
            }
        }
        return -1;
    }
};