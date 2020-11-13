class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {

        int n = input.size();
        if(k>n||k==0||n == 0) return {};
        vector<int> res(k,0);
        priority_queue<int> q;
        for(int i = 0;i<k;i++){
            q.push(input[i]);
        }
        for(int i = k;i<n;i++){
            if(q.top()>input[i]){
                q.pop();
                q.push(input[i]);
            }
        }
        for(int i = 0;i<k;i++){
            res[i] = q.top();
            q.pop();
        }
        return res;
    }
};