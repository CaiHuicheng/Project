/*
给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的中位数。

进阶：你能设计一个时间复杂度为 O(log (m+n)) 的算法解决此问题吗？


 示例 1：

 输入：nums1 = [1,3], nums2 = [2]
 输出：2.00000
 解释：合并数组 = [1,2,3] ，中位数 2
 示例 2：

 输入：nums1 = [1,2], nums2 = [3,4]
 输出：2.50000
 解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 示例 3：

 输入：nums1 = [0,0], nums2 = [0,0]
 输出：0.00000
 示例 4：

 输入：nums1 = [], nums2 = [1]
 输出：1.00000
 示例 5：

 输入：nums1 = [2], nums2 = []
 输出：2.00000

*/
#include<iostream>
#include<vector>

using namespace std;

int min(int nums1, int nums2) {
	return nums1 <= nums2 ? nums1 : nums2;
}

class Solution {
public:
	int getKeyElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
		int m = nums1.size();
		int n = nums2.size();
		int index1 = 0, index2 = 0;
		while (true) {
			//边界情况
			if (index1 == m) {
				return nums2[index2 + k - 1];
			}
			else if (index2 == n) {
				return nums1[index1 + k - 1];
			}
			if(k==1)
			{
				return min(nums1[index1], nums2[index2]);
			}
			//正常情况
			int newIndex1 = min(index1 + k / 2 - 1, m - 1);
			int newIndex2 = min(index2 + k / 2 - 1, n - 1);
			int pivot1 = nums1[newIndex1];
			int pivot2 = nums2[newIndex2];
			if (pivot1 <= pivot2) {
				k -= newIndex1 - index1 + 1;
				index1 = newIndex1 + 1;
			}
			else {
				k -= newIndex2 - index2 + 1;
				index2 = newIndex2 + 1;
			}
		}
	}
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int totalLength = nums1.size() + nums2.size();
		if (totalLength % 2 == 1) {
			return getKeyElement(nums1, nums2, (totalLength + 1) / 2);
		}
		else {
			return (getKeyElement(nums1, nums2, totalLength / 2) + getKeyElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
		}
	}
};


int main() {
	system("pause");
	return 0;
}