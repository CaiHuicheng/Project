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
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> s;
        long long inorder = (long long)INT_MIN-1;
        while(!s.empty()||root!=nullptr){
            while(root != nullptr){
                s.push(root);
                root = root->left;
            }
            //TreeNode * top = s.top();
            root = s.top();
            s.pop();
            // if(top->val<=inorder){
            //     return false;
            // }
            // inorder = top->val;
            // root = top->right;
            if(root->val <=inorder){
                return false;
            }
            inorder = root->val;
            root = root->right;
        }
        return true;
    }
};