class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int res=0;
        unordered_map<int,int> A_B;    
        //存储A+B
        for(int& a:A) for(int& b:B) ++A_B[a+b];
        //寻找相反数，相加
        for(int& c:C) for(int& d:D) res=res+A_B[-c-d];
        return res;
    }
};