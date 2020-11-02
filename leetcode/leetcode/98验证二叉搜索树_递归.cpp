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
        return helper(root,LONG_MIN,LONG_MAX);
    }
    bool helper(TreeNode* root, long long lower,long long upper){
        if(root == nullptr) return true;
        if(root->val <= lower||root->val>=upper){
            return false;
        }
        return helper(root->left,lower,root->val)&&helper(root->right,root->val,upper);
    }
};