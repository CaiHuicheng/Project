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
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int ans = 0;
        while(!q.empty()){
            int n = q.size();
            while(n>0){
                root = q.front();
                q.pop();
                if(root->left)q.push(root->left);
                if(root->right)q.push(root->right);
                n--;
            }
            ans++;
        }
        return ans;
    }
};