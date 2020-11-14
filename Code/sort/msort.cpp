#include<iostream>
#include<vector>

using namespace std;

void mSort(vector<int> &nums){
    for(int i = 0;i<nums.size()-1;i++){
        for(int j = 0;j<nums.size()-1-i;j++){
            if(nums[j]>nums[j+1])
                swap(nums[j],nums[j+1]);
        }
    }
}

int main()
{
    vector<int> nums = {1,3,4,2,7,8,4,3};
    mSort(nums);
    for(auto num:nums){
        cout<<num<<" ";
    }
    cout << endl;
	return 0;
}