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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        vector<vector<int>> res;
        vector<int> nums;
        vector<TreeNode *> s;
        queue<TreeNode*> st;
        st.push(root);
        while(!st.empty()){
            nums.clear();
            s.clear();
            while(!st.empty()){
                TreeNode* temp = st.front();
                st.pop();
                nums.push_back(temp->val);
                if(temp->left) s.push_back(temp->left);
                if(temp->right) s.push_back(temp->right);
            }
            res.push_back(nums);
            for(auto c:s){
                st.push(c);
            }
        }
        return res;
    }
};