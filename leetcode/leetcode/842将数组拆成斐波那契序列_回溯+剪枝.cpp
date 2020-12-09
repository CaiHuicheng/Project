class Solution {
public:
    vector<int> splitIntoFibonacci(string S) {
        vector<int> res;
        backtrack(res,S,S.length(),0,0,0);
        return res;
    }

    bool backtrack(vector<int> &res,string S,int n,int index, long long sum, int prev){
        if(index == n) {
            return (res.size() >= 3)?1:0;
        }
        long long curr = 0;
        for(int i = index;i<n;i++){
            if(i>index&&S[index] == '0'){
                break;
            }
            curr = curr*10+S[i]-'0';
            if(curr>INT_MAX){
                break;
            }
            if(res.size()>=2){
                if(curr<sum) continue;
                else if(curr>sum) break;
            }
            res.push_back(curr);
            if(backtrack(res,S,n,i+1,prev + curr, curr)) return true;
            res.pop_back();
        }
        return false;
    }
};