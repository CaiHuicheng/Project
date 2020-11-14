#include<iostream>
#include<vector>

using namespace std;

void shellSort(vector<int> &nums){
    int h = 1;
    while(h<nums.size()/3){
        h = 3*h+1;
    }
    while(h>=1){
        for(int i = h;i<nums.size();i++){
            for(int j = i;j>=h&&nums[j]<nums[j-h];j-=h){
                swap(nums[j],nums[j-h]);
            }
        }
        h = h/3;
    }
}

int main()
{
    vector<int> nums = {1,3,4,2,7,8,4,3,10,30,4,9,59};
    shellSort(nums);
    for(auto num:nums){
        cout<<num<<" ";
    }
    cout << endl;
	return 0;
}