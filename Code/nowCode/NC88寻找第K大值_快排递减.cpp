class Finder {
public:
    void quickSort(vector<int> &a,int left,int right){
        if(left<right){
            int mid = a[left];
            int low = left,high = right;
            while(low<high){
                while(a[high]>=mid&&low<high){
                    high--;
                }
                a[low] = a[high];
                while(a[low]<=mid&&low<high){
                    low++;
                }
                a[high] = a[low];
            }
            a[low] = mid;
            quickSort(a, left, low-1);
            quickSort(a, low+1, right);
        }
    }
    
    int findKth(vector<int> a, int n, int K) {
        // write code here
        if(K>n||n == 0) return 0;
        int left = 0,right=n-1;
        quickSort(a,left,right);
        return a[n-K];
    }
};