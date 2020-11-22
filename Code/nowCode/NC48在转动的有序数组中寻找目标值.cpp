class Solution {
public:
    /**
     * 
     * @param A int整型一维数组 
     * @param n int A数组长度
     * @param target int整型 
     * @return int整型
     */
    int search(int* A, int n, int target) {
        // write code here
        if(n == 0) return -1;
        int l = 0,r = n-1,mid = 0;
        while(l<=r){
            mid = (l+r)/2;
            if(A[mid] == target) return mid;
            if(A[mid]<A[l]){
                if(A[mid]<target&&A[r]>=target)
                    l = mid + 1;
                else
                    r = mid - 1;
            }else{
                if(A[mid]>target&&A[l]<=target)
                    r = mid - 1;
                else
                    l = mid + 1;
            }
        }
        return -1;
    }
};