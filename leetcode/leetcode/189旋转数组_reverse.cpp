class Solution {
public:
    // void rotate(vector<int>& nums, int k) {
    //     int n = nums.size();
    //     vector<int> newNums(n);
    //     for(int i =0;i<n;i++){
    //         newNums[(i+k)%n] = nums[i];
    //     }
    //     nums.assign(newNums.begin(),newNums.end());
    // }
    // void rotate(vector<int>& nums, int k) {
    //     int n = nums.size();
    //     k = k%n;
    //     int count = gcd(k,n);
    //     for(int start = 0;start<count;++start){
    //         int current = start;
    //         int prev = nums[start];
    //         do {
    //             int next = (current + k) % n;
    //             swap(nums[next],prev);
    //             current = next;
    //         }while(start!=current);
    //     }
    // }
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums,0,nums.size()-1);
        reverse(nums,0,k-1);
        reverse(nums,k,nums.size()-1);
    }

    void reverse(vector<int>& nums,int start,int end){
        while(start<end){
            swap(nums[start],nums[end]);
            start += 1;
            end -= 1;
        }
    }
};