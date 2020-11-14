#include<iostream>
#include<vector>

using namespace std;

int _quickSort(vector<int> &nums,int left,int right){
    int p = nums[left];
    while(left<right){
        while(left<right&&nums[right]>=p){
            right--;
        }
        nums[left] = nums[right];
        while(left<right&&nums[left]<=p){
            left++;
        }
        nums[right] = nums[left];
    }
    nums[left] = p;
    return left;
}
void quickSort(vector<int> &nums,int left,int right){
    if(left<right){
        int p = _quickSort(nums,left,right);
        quickSort(nums,left,p-1);
        quickSort(nums,p+1,right);
    }
}

int main()
{
    vector<int> nums = {1,3,4,2,7,8,4,3,10,30,4,9,59};
    int left = 0,right = nums.size()-1;
    quickSort(nums,left,right);
    for(auto num:nums){
        cout<<num<<" ";
    }
    cout << endl;
	return 0;
}