class Solution {
public:
//     void quickSort(vector<int> &a,int left,int right){
//         if(left<right){
//             int mid = a[left];
//             int low = left,high = right;
//             while(low<high){
//                 while(a[high]>=mid&&low<high){
//                     high--;
//                 }
//                 a[low] = a[high];
//                 while(a[low]<=mid&&low<high){
//                     low++;
//                 }
//                 a[high] = a[low];
//             }
//             a[low] = mid;
//             quickSort(a, left, low-1);
//             quickSort(a, low+1, right);
//         }
//     }
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        int n = input.size();
        if(k>n||k==0||n == 0) return {};
        vector<int> res(k,0);
        //quickSort(input,0,n-1);
        sort(input.begin(),input.end());
        for(int i = 0;i<k;i++){
            res[i] = input[i];
        }
        return res;
    }
};