class Solution {
public:
    /**
     * 二分查找
     * @param n int整型 数组长度
     * @param v int整型 查找值
     * @param a int整型vector 有序数组
     * @return int整型
     */
    int upper_bound_(int n, int v, vector<int>& a) {
        // write code here 
        int l = 0,r = n-1,mid = 0;
        while(l<r){
            mid = (r+l)/2;
            if(a[mid]>=v){
                if(mid == 0||a[mid-1]<v) return mid+1;
                else r = mid;
            }else{
                l = mid+1;
            }
        }
        return n+1;
    }
};