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
    TreeNode* invertTree(TreeNode* root) {
        //BFS
        if(root==nullptr) return root;
        queue<TreeNode*> bfs;
        bfs.push(root);

        while(!bfs.empty()){
            int size = bfs.size();

            for(int i = 0 ; i<size ; i++){
                TreeNode* temp = bfs.front();
                bfs.pop();
                swap(temp->left , temp->right);
                if(temp->left) bfs.push(temp->left);
                if(temp->right) bfs.push(temp->right);
            }
        }
        return root;
    }
};