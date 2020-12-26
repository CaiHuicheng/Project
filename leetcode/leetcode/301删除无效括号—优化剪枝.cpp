class Solution {
public:
    vector<string> ans;//此时不会重复搜索 无重复方案 直接存即可
    void dfs(string &s, int u, string res, int cnt, int l, int r){//cnt为当前左-右的值 l为需要删除的左括号数量 r为右
        //cout<<res<<endl;
        if(u==s.size()){
            if(!cnt) ans.push_back(res);
            return;
        }
        if(s[u]=='('){//在合法的条件下考虑删除 对于连续的k个'(' 只需考虑一次性 删 i个(0<=i<=k) 则可从2^k降到 k
            int k = u;
            while (k < s.size() && s[k] == '(') k ++;//找到最后一个连续的'('的右边
            l -= k - u;//假设将这些连续的'('全部删除
            for (int i = k - u; i >= 0; i -- ) {//i为删除后的位置
                if (l >= 0) dfs(s, k, res, cnt, l, r);//可删时
                res += '(', cnt ++, l ++ ;
            }
        }
        else if(s[u]==')'){//在合法的条件下考虑删除
            int k = u;
            while (k < s.size() && s[k] == ')') k ++;//找到最后一个连续的'('的右边
            r -= k - u;//假设将这些连续的'('全部删除
            for (int i = k - u; i >= 0; i -- ) {//i为删除后的位置
                if (cnt >= 0 && r >= 0) dfs(s, k, res, cnt, l, r);//可删时
                res += ')', cnt--, r++;
            }
        }
        else dfs(s,u+1,res + s[u],cnt,l,r);
    }
    vector<string> removeInvalidParentheses(string s) {
        int l = 0, r = 0;//l为当前左括号-右括号的值 r为需要删掉的右括号的值
        for(auto v : s){
            if(v=='(') l++;
            else if(v==')'){
                if(l <= 0) r++;//此时无效 右括号 必删
                else l--;//右括号+1 则左-右的值需要--   
            }  
        }
        //此时的l为需要删除的左括号数量 r为需要删除的右括号数量
        dfs(s,0,"",0,l,r);
        return ans;
    }
};