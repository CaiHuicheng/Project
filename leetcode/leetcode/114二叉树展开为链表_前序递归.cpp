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
        vector<TreeNode*> v;
        preorderTree(root,v);
        int n = v.size();
        for(int i = 1;i<n;i++){
            TreeNode* prev = v.at(i-1),*cur =v.at(i);
            prev->left = nullptr;
            prev->right = cur;
        }
    }
    void preorderTree(TreeNode*root,vector<TreeNode*>& v){
        if(root!=nullptr){
            v.push_back(root);
            preorderTree(root->left,v);
            preorderTree(root->right,v);
        }
    }
};