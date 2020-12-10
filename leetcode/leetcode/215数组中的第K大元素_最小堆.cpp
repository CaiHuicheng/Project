class Solution {
   public:
    int findKthLargest(vector<int>& nums, int k) {
        // 对前k个元素建成小根堆
        for (int i = 0; i < k; i++) {
            swim(nums, i);
        }
        // 剩下的元素与堆顶比较，若大于堆顶则去掉堆顶，再将其插入
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] > nums[0]) {
                swap(nums[0], nums[i]);
                sink(nums, 0, k - 1);
            }
        }
        // 结束后第k个大的数就是小根堆的堆顶
        return nums[0];
    }

   private:
    // 若v1比v2优先度高，返回true
    bool priorityThan(int v1, int v2) { return v1 < v2; }

    // 上浮 从下到上调整堆
    void swim(vector<int>& heap, int i) {
        while (i > 0 && priorityThan(heap[i], heap[(i - 1) / 2])) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    // 下沉 从下到上调整堆
    void sink(vector<int>& heap, int i, int N) {
        while (2 * i + 1 <= N) {
            int j = 2 * i + 1;
            if (j + 1 <= N && priorityThan(heap[j + 1], heap[j])) {
                j++;
            }
            if (priorityThan(heap[i], heap[j])) {
                break;
            }
            swap(heap[i], heap[j]);
            i = j;
        }
    }
};