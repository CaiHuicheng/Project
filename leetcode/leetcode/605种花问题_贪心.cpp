class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int count = 0;
        int nums = flowerbed.size();
        int prev = -1;
        for(int i = 0;i<nums;i++){
            if(flowerbed[i] == 1){
                if(prev<0) count += i/2;
                else count += (i-prev-2)/2;
                prev = i;
            }
        }
        if(prev < 0) count += (nums+1)/2;
        else count += (nums - prev -1)/2;
        return count >= n;
    }
};