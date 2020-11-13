/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if(nullptr == root) return {};
        vector<int> res;
        stack<TreeNode*> st;
        TreeNode* tail = nullptr;
        while(root||!st.empty()){
            while(root){
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            if(root->right==nullptr||root->right == tail){
                res.push_back(root->val);
                tail = root;
                root = nullptr;
            }else{
                st.push(root);
                root = root->right;
            }
        }
        return res;
    }
};