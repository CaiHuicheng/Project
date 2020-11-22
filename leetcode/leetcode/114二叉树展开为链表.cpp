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
    void flatten(TreeNode* root) {
        if(root == nullptr) return;
        stack<TreeNode*> st;
        st.push(root);
        TreeNode *node = nullptr;
        while(!st.empty()){
            TreeNode *cur = st.top();st.pop();
            if(node!=nullptr){
                node->left = nullptr;
                node->right = cur;
            }
            if(cur->right)st.push(cur->right);
            if(cur->left)st.push(cur->left);
            node = cur;
        }
    }
};