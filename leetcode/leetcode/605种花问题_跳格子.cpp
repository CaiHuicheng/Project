class Solution {
public:
    //统计0
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        for(int i = 0;i<flowerbed.size()&&n>0;){
            if(flowerbed[i] == 1){
                i += 2;
            }else if(i == flowerbed.size()-1||flowerbed[i+1] == 0){
                n--;
                i+=2;     
            }else{
                i+=3;
            }
        }
        return n<=0;
    }
};