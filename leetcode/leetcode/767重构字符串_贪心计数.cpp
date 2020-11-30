class Solution {
public:
    string reorganizeString(string S) {
        if(S.length()<2) return S;
        vector<int> counts(26,0);
        int maxCount = 0;
        int len = S.length();
        for(int i = 0;i<len;i++){
            counts[S[i]-'a']++;
            maxCount = max(maxCount,counts[S[i]-'a']);
        }
        if(maxCount>(len+1)/2) return "";
        string reorganizeArray(len,' ');
        int evenIndex = 0,oddIndex = 1;
        int halfLen = len/2;
        for(int i= 0 ;i<26;i++){
            char c = 'a'+i;
            while(counts[i]>0&&counts[i]<=halfLen&&oddIndex<len){
                reorganizeArray[oddIndex] = c;
                counts[i] --;
                oddIndex+=2;
            }
            while(counts[i]>0){
                reorganizeArray[evenIndex] = c;
                counts[i]--;
                evenIndex+=2;
            }
        }
        return reorganizeArray;
    }
};