class Solution{
public:
    int binarySearch(vector<int>& nums,int target,bool lower){
        int left = 0;
        int right = (int)nums.size()-1;
        int ans = (int)nums.size();
        while(left<=right){
            int mid = (left+right)/2;
            if(nums[mid]>target||(lower&&nums[mid] >= target)){
                right = mid - 1;
                ans = mid;
            }else{
                left = mid + 1;
            }
        }
        return ans;
    }
    vector<int> searchRange(vector<int>& nums,int target){
        int leftIndex = binarySearch(nums,target,true);
        int rightIndex = binarySearch(nums,target,false)-1;
        if(leftIndex<=rightIndex && rightIndex<nums.size()&&nums[leftIndex] == target&&nums[rightIndex] == target){
            return vector<int> {leftIndex,rightIndex};
        }
        return vector<int>{-1,-1};
    }
};