class Solution {
public:
    void work(const string &str, int lc, int rc, int n, vector<string> &res) {
        if(str.size() == n) {
            res.push_back(str);
            return;
        }
        if(rc < lc) {
            work(str+")", lc, rc+1, n, res);
        }
        if(lc+1-rc <= n-str.size()-1) {
            work(str+"(", lc+1, rc, n, res);
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        work("", 0, 0, n*2, res);
        return res;
    }
};
