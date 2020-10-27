class Solution {
public:
    int minArray(vector<int>& numbers) {
        int low = 0;
        int hight = numbers.size()-1;
        while(low<hight){
            int p = low + (hight-low)/2;
            if(numbers[p]<numbers[hight]) hight = p;
            else if(numbers[p]>numbers[hight]) low = p+1;
            else hight-=1; 
        }
        return numbers[low];
    }
};