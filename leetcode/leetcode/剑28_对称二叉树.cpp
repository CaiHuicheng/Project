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
    bool isSymmetric(TreeNode* root) {
        return !root?true:jude(root->left,root->right);
    }
    bool jude(TreeNode* p,TreeNode* q){
        if(!p&&!q)return true;
        if(!p||!q)return false;
        if(p->val != q->val) return false;
        return jude(p->left,q->right)&&jude(p->right,q->left);
    }
};