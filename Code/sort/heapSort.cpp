#include<iostream>
#include<vector>

using namespace std;


void max_heapify(vector<int>&nums,int start,int end){
    // 建立父節點指標和子節點指標
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { // 若子節點指標在範圍內才做比較
        if (son + 1 <= end && nums[son] < nums[son + 1]) // 先比較兩個子節點大小，選擇最大的
            son++;
        if (nums[dad] > nums[son]) // 如果父節點大於子節點代表調整完畢，直接跳出函數
            return;
        else { // 否則交換父子內容再繼續子節點和孫節點比較
            swap(nums[dad], nums[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(vector<int>&nums,int start,int end) {
    int len = end-start;
    // 初始化，i從最後一個父節點開始調整
    for (int i = len / 2 - 1; i >= 0; i--)
        max_heapify(nums, i, len - 1);
    // 先將第一個元素和已经排好的元素前一位做交換，再從新調整(刚调整的元素之前的元素)，直到排序完畢
    for (int i = len - 1; i > 0; i--) {
        swap(nums[0], nums[i]);
        max_heapify(nums, 0, i - 1);
    }
}


int main()
{
    vector<int> nums = {1,3,4,2,7,8,4,3,10,30,4,9,59};
    int left = 0,right = nums.size();
    heap_sort(nums,left,right);
    for(auto num:nums){
        cout<<num<<" ";
    }
    cout << endl;
	return 0;
}