class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(k == 0) return;
        int n = nums.size();
        k = k%n;
        int count = 0;
        for(int i=0;count<n;i++){
            int cur = i;
            int prev = nums[i];
            do{
                int next = (cur+k)%n;
                int temp = nums[next];
                nums[next] = prev;
                prev = temp;
                cur = next;
                count++;
            }while(i != cur);
        }
    }
};