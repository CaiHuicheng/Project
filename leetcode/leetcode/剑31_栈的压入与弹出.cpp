class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        if(popped.size()!=pushed.size())return false;
        if(pushed.size() == 1&&pushed.size()==popped.size()) return true;
        stack<int> s;
        int n = popped.size();
        int j = 0;
        for(int i = 0; i<pushed.size(); ++i){
            s.push(pushed[i]);
            while(!s.empty()&&s.top() == popped[j]&&j<n){
                s.pop();
                j++;
            }
        }
        return s.empty();
    }
};