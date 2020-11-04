class Solution {
private:
    struct Data{
        string str;
        int left;
        int right;
        int status;
    };
    stack<Data> st;
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        if(n == 0) return res;
        n *= 2;
        st.push(Data{"",0,0,0});
        while(!st.empty()){
            Data &t = st.top();
            if(t.str.size() == n){
                res.push_back(t.str);
                st.pop();
                continue;
            }
            if(t.status == 0){
                if(t.right+1<=t.left){
                    st.push(Data{t.str+")",t.left,t.right+1,0});
                }
                t.status = 1;
                continue;
            }
            if(t.status == 1){
                if(t.left+1-t.right<=n-t.str.size()-1){
                    st.push(Data{t.str+"(",t.left+1,t.right,0});
                }
                t.status = 2;
                continue;
            }
            if(t.status == 2) {
                st.pop();
                continue;
            }
        }
        return res;
    }
};