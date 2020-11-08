class Solution {
public:
    /*
    1、暴力法
        初始化ans = 0
        从左向右扫描数组：
            初始化max_left = 0,max_right = 0
            从当前元素向左扫描并更新：
                max_left = max(max_left,height[j])
            从当前元素向右扫描并更新:
                max_right = max(max_right,height[j])；
            将min(max_left,max_right)-height[i]累加到ans；
    */
    int trap(vector<int>& height) {
        int ans = 0;
        int size = height.size();
        for(int i = 0;i<size-1;i++){
            int max_l = 0,max_r = 0;
            for(int j = i;j>=0;j--){
                max_l = max(max_l,height[j]);
            }
            for(int j =i;j<size;j++){
                max_r = max(max_r,height[j]);
            }
            ans += min(max_l,max_r) - height[i];
        }
        return ans;
    }
};