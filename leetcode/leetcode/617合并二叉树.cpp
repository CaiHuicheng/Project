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
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if(nullptr == t1) return t2;
        if(nullptr == t2) return t1;
        TreeNode* merged = new TreeNode(t1->val+t2->val);
        merged->left = mergeTrees(t1->left,t2->left);
        merged->right = mergeTrees(t1->right,t2->right);
        return merged;
    }
};