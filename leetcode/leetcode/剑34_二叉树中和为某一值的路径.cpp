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
    vector<vector<int>> all_path;
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(nullptr == root) return all_path;
        vector<int> path;
        find_path(root,sum,path);
        return all_path;
    }
    void find_path(TreeNode* root,int sum,vector<int> path){
        if(nullptr == root)return ;
        path.push_back(root->val);
        if(sum == root->val && root->left == nullptr && root->right == nullptr){
            all_path.push_back(path);
        }
        find_path(root->left,sum-root->val,path);
        find_path(root->right,sum-root->val,path);
        path.pop_back();
    }
};