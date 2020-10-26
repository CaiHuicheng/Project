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
   
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
       if(preorder.empty()||preorder.size()!=inorder.size())return nullptr;
       int pS=0,iS=0;
       int pE=preorder.size()-1,iE=inorder.size()-1;
       return binaryTree(preorder,inorder,pS,pE,iS,iE);
    }
    TreeNode* binaryTree(vector<int>& preorder,vector<int>& inorder,int ps,int pe,int is,int ie){
        if(ps>pe||is>ie)return nullptr;
        TreeNode * root = new TreeNode(preorder[ps]);
        int iRoot = 0;
        for(auto i:inorder){
            if(i != preorder[ps])iRoot++;
            else break;   
        }
        root->left = binaryTree(preorder,inorder,ps+1,ps+iRoot-is,is,iRoot-1);
        root->right= binaryTree(preorder,inorder,pe-(ie-iRoot)+1,pe,iRoot+1,ie); 
        return root;
    }
};