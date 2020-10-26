/*
给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

注意:

每个数组中的元素不会超过 100
数组的大小不会超过 200
示例 1:

输入: [1, 5, 11, 5]

输出: true

解释: 数组可以分割成 [1, 5, 5] 和 [11].

*/

#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;
#define MAX_N 256
//方法一 ：递归 时间超时
class  Solution
{
	//考虑处理[0,i]范围内所有的数字，看是否填满sum/2背包
	bool canPartition_i(vector<int>& nums, int mid_sum, int i) {
		if (mid_sum < 0 || i < 0)return false;
		if (mid_sum == 0)return true;
		return canPartition_i(nums, mid_sum, i - 1) || canPartition_i(nums, mid_sum - nums[i], i - 1);
	}
public:
	bool canPartition(vector<int>& nums) {
		int sum = 0;
		int n = nums.size();
		for (int i = 0; i < n; i++)
		{
			sum += nums[i];
		}
		if (sum % 2 != 0)return false;
		return canPartition_i(nums, sum / 2, n - 1);
	}
};

//动态规划 0-1背包
/*
01背包还有一种问题就是利润最大，上面的是能否装满。
i 是物体的下标，j是当前的最大体积
dp[i][j]=Math.max(dp[i-1][j],dp[i-1][j-w[i]]+v[i])
特殊(当前装不下)
dp[i][j]=dp[i-1][j]

二维也是和上面相似
dp[j]=Math.max(dp[j],dp[j-w[i]]+v[i]);
*/
class Solution {
private:

public:
	bool canPartition(vector<int>& nums) {
		int sum = 0;
		int n = nums.size();
		for (int i = 0; i<n; i++)
		{
			sum += nums[i];
		}
		if (sum % 2 != 0)return false;
		//dp[i] 表示在数字范围内，能否能充容量为i的背包
		//dp[j] = dp[j] || dp[j - nums[i]](nums[i] <= j <= target)
		vector<bool>dp(sum / 2 + 1, false);
		for (int i = 0; i<sum / 2 + 1; i++)
		{
			dp[i] = (nums[0] == i);
		}
		for (int i = 1; i<n; i++)
			for (int j = sum / 2; j >= nums[i]; j--)
				dp[j] = dp[j] || dp[j - nums[i]];

		return dp[sum / 2];
	}
};

//C语言版 动态规划
/*
bool canPartition(int* nums, int numsSize) {
int sum = 0;
for (int i = 0; i<numsSize; i++) {
sum += nums[i];
}
if (sum % 2 != 0) {
return false;
}
sum /= 2;
//初始化dp
int dp[sum + 1];
memset(dp, 0, sizeof(dp));    //当没有数字的时候为假
dp[0] = 1;                    //当和为0的时候，即使没有数字也为真
//更新dp
for (int i = 0; i<numsSize; i++) {
for (int j = sum; j>0; j--) {     //会用到比j小的元素，因此从右往左更新
if (j >= nums[i]) {     //当j<nums[i]的时候，直接继承
//当j能被前i-1个数表示或者j-nums[i]能被前i-1个数表示时都行
dp[j] = dp[j] || dp[j - nums[i]];
}
}
}
return dp[sum];
}
*/
bool canPartition(int* nums, int numsSize)
{
	int sum = 0;
	int i, j;
	int tar;
	
	bool dp[MAX_N][10001] = { 0 };
	for (i = 0; i< numsSize; i++) {
		sum += nums[i];
	}
	if (sum % 2 == 1) {
		return false;
	}
	tar = sum / 2;

	for (j = 0; j <= tar; j++) {
		if (nums[0] == j) {
			dp[0][j] = true;
		}
	}
	for (i = 1; i < numsSize; i++) {
		for (j = 0; j <= tar; j++) {
			if (j < nums[i]) {
				dp[i][j] = dp[i - 1][j];
			}
			else {
				dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i]];
			}
		}
	}

	return dp[numsSize - 1][tar];
}


int main()
{
	int n;
	cin >> n;
	vector<int> a(n);
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
		sum += a[i];
	}
	vector<vector<int> > dp(n + 1, vector<int>(sum / 2 + 1, 0));
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= sum / 2; ++j)
		{
			if (j >= a[i - 1])
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - a[i - 1]] + a[i - 1]);
			else
				dp[i][j] = dp[i - 1][j];
		}
	}
	bool flag = (sum - 2 * dp[n][sum / 2] == 0);
	if (flag)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
	return 0;
}