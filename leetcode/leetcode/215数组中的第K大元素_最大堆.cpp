class Solution {
public:
    void maxHeapify(vector<int>& nums, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && nums[l] > nums[largest]) {
            largest = l;
        } 
        if (r < heapSize && nums[r] > nums[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(nums[i], nums[largest]);
            maxHeapify(nums, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<int>& nums,int heapSize){
        for(int i = heapSize / 2; i >= 0; --i)
            maxHeapify(nums, i, heapSize);
    }

    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildMaxHeap(nums,heapSize);
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) {
            swap(nums[0], nums[i]);
            --heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};