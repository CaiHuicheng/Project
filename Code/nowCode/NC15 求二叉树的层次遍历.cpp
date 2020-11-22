/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 * };
 */

class Solution {
public:
    /**
     * 
     * @param root TreeNode类 
     * @return int整型vector<vector<>>
     */
    vector<vector<int> > levelOrder(TreeNode* root) {
        // write code here
        vector<vector<int>> res;
        if(root == nullptr) return res; 
        vector<int> ans;
        vector<TreeNode*> v;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            v.clear();
            ans.clear();
            while(!q.empty()){
                root = q.front();q.pop();
                ans.push_back(root->val);
                if(root->left) v.push_back(root->left);
                if(root->right) v.push_back(root->right);
            }
            res.push_back(ans);
            for(auto s:v){
                q.push(s);
            }
        }
        return res;
    }
};