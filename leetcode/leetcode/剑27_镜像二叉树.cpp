/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if(nullptr == root) return nullptr;
        stack<TreeNode*> s;
        s.push(root);
        while(!s.empty()){
            TreeNode* top = s.top();
            s.pop();
            // TreeNode* temp = top->left;
            // top->left = top->right;
            // top->right = temp;
            swap(top->left,top->right);
            if(top->left)s.push(top->left);
            if(top->right)s.push(top->right);
        }
        return root;
    }
};