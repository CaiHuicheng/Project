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
     * @param root TreeNode类 the root of binary tree
     * @return int整型vector<vector<>>
     */
    stack<TreeNode*> st;
    vector<int> preorderTree(TreeNode* root){
        if(nullptr == root) return {};
        vector<int> res;
        while(root||!st.empty()){
            while(root){
                res.push_back(root->val);
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            root = root->right;
        }
        return res;
    }
    
    vector<int> inorderTree(TreeNode* root){
        if(nullptr == root) return {};
        vector<int> res;
        while(root||!st.empty()){
            while(root){
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
    vector<int> postorderTree(TreeNode* root){
        if(nullptr == root) return {};
        vector<int> res;
        TreeNode* temp = nullptr;
        while(root||!st.empty()){
            while(root){
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            if(root->right == nullptr||root->right == temp){
                res.push_back(root->val);
                temp = root;
                root = nullptr;
            }else{
                st.push(root);
                root =root->right;
            }
            
        }
        return res;
    }
    
    vector<vector<int> > threeOrders(TreeNode* root) {
        // write code here
        vector<vector<int>> res;
        res.push_back(preorderTree(root));
        res.push_back(inorderTree(root));
        res.push_back(postorderTree(root));
        return res;
    }
};