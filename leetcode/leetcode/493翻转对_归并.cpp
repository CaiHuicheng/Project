class Solution {
public:
    int _reversePairs(vector<int>& nums,int left,int right){
        if(left == right) return 0;
        else{
            int mid = (left+right)/2;
            int n1 = _reversePairs(nums,left,mid);
            int n2 = _reversePairs(nums,mid+1,right);
            int res = n1+n2;
            
            int i = left;
            int j = mid+1;
            while(i<=mid){
                while(j<=right&&(long long)nums[i]>2*(long long)nums[j])j++;
                res+=(j-mid-1);
                i++;
            }
            vector<int> sorted(right-left+1);
            int p1 = left,p2 = mid+1;
            int p = 0;
            while(p1<=mid||p2<=right){
                if(p1>mid) sorted[p++] = nums[p2++];
                else if(p2>right) sorted[p++] = nums[p1++];
                else{
                    if(nums[p1]<nums[p2]) sorted[p++] = nums[p1++];
                    else sorted[p++] = nums[p2++];
                }
            }
            for(int i = 0;i<sorted.size();i++){
                nums[left+i] = sorted[i];
            }
            return res;
        }
    }
    int reversePairs(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        return _reversePairs(nums,0,nums.size()-1);
    }
};