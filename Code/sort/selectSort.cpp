#include<iostream>
#include<vector>

using namespace std;

void selectSort(vector<int> &nums){
    for(int i = 0;i<nums.size()-1;i++){
        int min = i;
        for(int j = i+1;j<nums.size();j++){
            if(nums[j]<nums[min])
                min = j;
        }
        swap(nums[i],nums[min]);
    }
}

int main()
{
    vector<int> nums = {1,3,4,2,7,8,4,3};
    selectSort(nums);
    for(auto num:nums){
        cout<<num<<" ";
    }
    cout << endl;
	return 0;
}