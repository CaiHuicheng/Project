class Solution {
public:
    //统计0
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        if(flowerbed.empty()) return n == 0;
        int countOfZero = 1;
        int canPalce = 0;
        for(auto bed:flowerbed){
            if(bed == 0) countOfZero++;
            else{
                canPalce+=(countOfZero-1)/2;
                if(canPalce>=n) return true;
                countOfZero = 0;
            }
        }
        //最后一段0区还未结算：
        countOfZero++;// 最后再预设1个0，因为最后花坛的最右边没有花，可以认为存在一个虚无的0
        canPalce+=(countOfZero-1)/2;
        return canPalce>=n;
    }
};