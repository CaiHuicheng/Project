
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if(numbers.size()==0) return 0;
        int result = numbers[0];
        int count=1;
        for(int i=1; i<numbers.size(); i++)
        {
            if(numbers[i]==result) count++;
            else count--;
            if(count==0) 
            {
                result = numbers[i];
                count = 1;
            }
        }
        count=0;
        for(int i=0; i<numbers.size(); i++)
        {
            if(numbers[i]==result) count++;
        }
        return count>numbers.size()/2 ? result:0;
    }
};