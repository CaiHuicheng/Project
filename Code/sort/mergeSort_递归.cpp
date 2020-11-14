#include<iostream>
#include<vector>

using namespace std;

//递归
void mergeSort_recursive(vector<int> &nums,vector<int> &mergeNums,int start,int end){
    if(start>=end){
        return;
    }
    int len = end - start,mid = (len>>1)+start;
    int start1 = start,end1 = mid;
    int start2 = mid+1,end2 = end;
    mergeSort_recursive(nums,mergeNums,start1,end1);
    mergeSort_recursive(nums,mergeNums,start2,end2);
    int k = start;
    while(start1<=end1&&start2<=end2){
        mergeNums[k++] = nums[start1]<nums[start2]?nums[start1++]:nums[start2++];
    }
    while(start1<=end1){
        mergeNums[k++] = nums[start1++];
    }
    while(start2<=end2){
        mergeNums[k++] = nums[start2++];
    }
    for(k = start;k<=end;k++){
        nums[k] = mergeNums[k];
    }
}

void mergeSort(vector<int> &nums){
    vector<int> mergeNums(nums.size());
    mergeSort_recursive(nums,mergeNums,0,nums.size()-1);
}

int main()
{
    vector<int> nums = {1,3,4,2,7,8,4,3,10,30,4,9,59};
    mergeSort(nums);
    for(auto num:nums){
        cout<<num<<" ";
    }
    cout << endl;
	return 0;
}