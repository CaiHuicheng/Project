/*
����һ��ֻ�����������ķǿ����顣�Ƿ���Խ��������ָ�������Ӽ���ʹ�������Ӽ���Ԫ�غ���ȡ�

ע��:

ÿ�������е�Ԫ�ز��ᳬ�� 100
����Ĵ�С���ᳬ�� 200
ʾ�� 1:

����: [1, 5, 11, 5]

���: true

����: ������Էָ�� [1, 5, 5] �� [11].

*/

#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;
#define MAX_N 256
//����һ ���ݹ� ʱ�䳬ʱ
class  Solution
{
	//���Ǵ���[0,i]��Χ�����е����֣����Ƿ�����sum/2����
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

//��̬�滮 0-1����
/*
01��������һ������������������������ܷ�װ����
i ��������±꣬j�ǵ�ǰ��������
dp[i][j]=Math.max(dp[i-1][j],dp[i-1][j-w[i]]+v[i])
����(��ǰװ����)
dp[i][j]=dp[i-1][j]

��άҲ�Ǻ���������
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
		//dp[i] ��ʾ�����ַ�Χ�ڣ��ܷ��ܳ�����Ϊi�ı���
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

//C���԰� ��̬�滮
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
//��ʼ��dp
int dp[sum + 1];
memset(dp, 0, sizeof(dp));    //��û�����ֵ�ʱ��Ϊ��
dp[0] = 1;                    //����Ϊ0��ʱ�򣬼�ʹû������ҲΪ��
//����dp
for (int i = 0; i<numsSize; i++) {
for (int j = sum; j>0; j--) {     //���õ���jС��Ԫ�أ���˴����������
if (j >= nums[i]) {     //��j<nums[i]��ʱ��ֱ�Ӽ̳�
//��j�ܱ�ǰi-1������ʾ����j-nums[i]�ܱ�ǰi-1������ʾʱ����
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