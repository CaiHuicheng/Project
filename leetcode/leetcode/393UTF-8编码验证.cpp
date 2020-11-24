class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int p=0;
        while(p<data.size()){
            int v = data[p];
            int cnt = 0;
            if((v&0b10000000) == 0){
                cnt = 0;
            }else if((v&0b11100000) == 0b11000000){
                cnt = 1;
            }else if((v&0b11110000) == 0b11100000){
                cnt = 2;
            }else if((v&0b11111000) == 0b11110000){
                cnt = 3;
            }else{
                return false;
            }
            p++;
            while(p<data.size()&&cnt>0){
                if((data[p]&0b11000000)!=0b10000000) break;
                p++;
                cnt--;
            }
            if(cnt>0) return false;
        }
        return true;
    }
};