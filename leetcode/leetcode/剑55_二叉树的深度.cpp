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
        if(nullptr == root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        while(!q.empty()){
            int size = q.size();
            depth++;
            for(int i = 0;i<size;i++){
                TreeNode * front = q.front();
                q.pop();
                if(front->left) q.push(front->left);
                if(front->right)q.push(front->right);
            }
        }
        return depth;
    }
};