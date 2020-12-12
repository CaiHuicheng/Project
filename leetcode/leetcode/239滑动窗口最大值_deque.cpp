class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if(k == 0) return res;
        deque<int> window;   //双端队列，从队头到队尾 依次存 窗口内最大元素的index ~ 最小元素的index

        int right = 0;
        while(right < nums.size()){   //后续，窗口每右移一次，都会产生一个最大值[队列头位置的元素]
            if(!window.empty() && window.front() <= right - k){   //队头不在窗口范围内
                window.pop_front();
            }
            while(!window.empty() && nums[right] > nums[window.back()]){   //待入队元素比队尾元素大
                window.pop_back();
            }
            window.push_back(right);
            right++;
            if(right >= k) res.push_back(nums[window.front()]);
        }
        return res;
    }
};