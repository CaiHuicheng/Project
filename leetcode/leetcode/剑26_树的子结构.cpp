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
    bool FindBToA(TreeNode* A,TreeNode* B){
        //B树遍历结束 返回true
        if(NULL == B) return true;
        //A树遍历结束 返回false
        if(NULL == A) return false;
        if(A->val!=B->val) return false;
        return FindBToA(A->left,B->left)&&FindBToA(A->right,B->right);
    }

    bool isSubStructure(TreeNode* A, TreeNode* B) {
        bool res = false;
        if(NULL == A||NULL == B) return false;
        //根节点相同
        if(A->val == B->val) res = FindBToA(A,B);
        //遍历A树的左子树
        if(!res) res = isSubStructure(A->left,B);
        //左子树找不到，遍历右子树
        if(!res) res = isSubStructure(A->right,B);
        return res;
    }
};