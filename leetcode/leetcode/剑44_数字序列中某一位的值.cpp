class Solution {
public:
    int findNthDigit(int n) {
        // long base = 9,digits = 1,num = 0,targetNum = 1;
        // auto index = 0;
        // while(n-base*digits > 0){
        //     n -=base*digits;
        //     base *= 10;
        //     digits ++;
        // }
        // for(auto i = 1;i<digits;++i) {
        //     targetNum = targetNum*10;
        // }
        // index = n % digits;
        // if(index == 0) index = digits;
        // targetNum += (index == digits)? n/digits-1:n/digits;
        // for(int i = index;i<digits;++i){
        //     targetNum /= 10;
        // }
        // return targetNum%10;
        n -= 1;
        for (long digits=1;digits < 11;++digits ){
            int first_num = pow(10,digits-1);
            if (n < 9 * first_num * digits){
                return int(to_string(first_num + n/digits)[n%digits])-'0';
            }
            n -= 9 * first_num * digits;
        }
        return 0;

    }
};
