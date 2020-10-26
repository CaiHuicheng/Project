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
    // bool _isBalanced(TreeNode*root,int depth){
    //     if(NULL == root) return true;
    //     int left = 0;
    //     int right = 0;
    //     if(_isBalanced(root->left,left)&&_isBalanced(root->right,right)){
    //         if(abs(left-right)>1) return false;
    //         depth = (left>right?left:right)+1;
    //         return true;
    //     }
    //     return false;
    // }
    // bool isBalanced(TreeNode* root) {
    //     int depth;
    //     return _isBalanced(root,depth);
    // }
    bool isBalanced(TreeNode* root) {
        return !root?true:abs(depth(root->left)-depth(root->right))<=1&&isBalanced(root->left)&&isBalanced(root->right);
    }
    int depth(TreeNode* root){
        return !root?0:max(depth(root->left),depth(root->right))+1;
    }
};