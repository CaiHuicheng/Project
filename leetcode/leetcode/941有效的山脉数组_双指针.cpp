class Solution {
public:
    bool validMountainArray(vector<int>& arr) {
        if(arr.size()<3) return false;
        int n = arr.size();
        int l = 0,r = n-1;
        while(l+1<n&&arr[l]<arr[l+1]){
            l++;
        }
        while(r-1>0&&arr[r-1]>arr[r]){
            r--;
        }
        if(r == l&&l>0&&r<n-1) return true;
        return false;
    }
};