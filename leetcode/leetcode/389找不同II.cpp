class Solution {
public:
    char findTheDifference(string s, string t) {
        int num1 = 0,num2=0;
        for(auto c:s){
            num1 += c;
        }
        for(auto c:t){
            num2 += c;
        }
        return num2-num1;
    }
};