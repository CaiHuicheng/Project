/*
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

 

 示例:

 给定 nums = [2, 7, 11, 15], target = 9

 因为 nums[0] + nums[1] = 2 + 7 = 9
 所以返回 [0, 1]
*/
#include<iostream>
#include<stdio.h>
#include<vector>
#include<map>

using namespace std;

//暴力破解
class Solution01 {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		int i, j;
		for (i = 0; i<nums.size() - 1; i++) {
			for (j = i + 1; j<nums.size(); j++) {
				if (nums[i] + nums[j] == target) {
					return{ i,j };
				}
			}
		}
		return{ i,j };
	}
};
//两遍哈希表
class Solution02 {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		map<int, int> a;//建立hash表存放数组元素
		vector<int> b(2, -1);//存放结果
		for (int i = 0; i < nums.size(); i++)
			a.insert(map<int, int>::value_type(nums[i], i));
		//map<int, int>::iterator mapA;
		/*for (mapA = a.begin(); mapA != a.end(); mapA++) {
			cout << " " << mapA->first << "\t|" << mapA->second << endl;
		}*/
		for (int i = 0; i<nums.size(); i++)
		{
			cout<<target-nums[i]<<endl;
			if (a.count(target - nums[i])>0 && (a[target - nums[i]] != i))
				//判断是否找到目标元素且目标元素不能是本身
			{
				b[0] = i;
				b[1] = a[target - nums[i]];
				cout << "b[0]:" << b[0] << " b[1]:" << b[1] << endl;
				break;
			}
		}
		return b;
	};
};

//一遍哈希表
class Solution03 {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		map<int, int> a;//提供一对一的hash
		vector<int> b(2, -1);//用来承载结果，初始化一个大小为2，值为-1的容器b
		for (int i = 0; i<nums.size(); i++)
		{
			if (a.count(target - nums[i])>0)
			{
				b[0] = a[target - nums[i]];
				b[1] = i;
				break;
			}
			a[nums[i]] = i;//反过来放入map中，用来获取结果下标
		}
		return b;
	};
};



int main() {
	Solution02 solution;
	int num[] = { 2, 7, 11, 15 };
	vector<int> nums;
	for (int i = 0; i < sizeof(num)/sizeof(int); i++)
	{
		nums.push_back(num[i]);
	}
	int target = 18;
	solution.twoSum(nums, target);
	system("pause");
	return 0;
}