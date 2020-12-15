class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        string strNum = to_string(N);
        int flag = strNum.size();
        for(int i = strNum.size()-1;i>0;i--){
           if(strNum[i-1]>strNum[i]){
                strNum[i-1]--;
                for(int j = i;j<strNum.size();j++){
                    strNum[j] = '9';
                }
           }
        }
        return stoi(strNum);
    }
};