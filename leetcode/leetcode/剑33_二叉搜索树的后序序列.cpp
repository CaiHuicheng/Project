class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        stack<int> s;
        //因为搜索二叉树的右>根>左,人为确定根最大，即根>右>左，即后序的逆序
        int MaxRoot = INT_MAX;
        for(int i = postorder.size()-1;i>=0;--i){
            if(postorder[i]>MaxRoot) return false;
            //左子树出现
            while(!s.empty()&&postorder[i]<s.top()){
                MaxRoot = s.top();
                s.pop();
            }
            s.push(postorder[i]);
        }
        return true;
    }
};