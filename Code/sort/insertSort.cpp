#include<iostream>
#include<vector>

using namespace std;

void insertSort(vector<int> &nums){
    for(int i = 1;i<nums.size();i++){
        int key = nums[i];
        int j = i-1;
        while(j>=0&&key<nums[j]){
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = key;
    }
}

int main()
{
    vector<int> nums = {1,3,4,2,7,8,4,3,10,30,4,9,59};
    insertSort(nums);
    for(auto num:nums){
        cout<<num<<" ";
    }
    cout << endl;
	return 0;
}