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
private:
    unordered_map<int, int> index;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for(int i=0;i<n;i++){
            index[inorder[i]] = i;
        }
        return _buildTree(preorder,inorder,0,n-1,0,n-1);
    }

    TreeNode* _buildTree(const vector<int>& preorder,const vector<int>& inorder,int pl,int pr,int il,int ir){
        if(pl>pr) return nullptr;
        // 前序遍历中的第一个节点就是根节点
        int proot = pl;
        // 在中序遍历中定位根节点
        int iroot = index[preorder[proot]];
        // 先把根节点建立出来
        TreeNode* root = new TreeNode(preorder[proot]);
        // 得到左子树中的节点数目
        int size_left_subtree = iroot-il;
        // 递归地构造左子树，并连接到根节点
        // 先序遍历中「从 左边界+1 开始的 size_left_subtree」个元素就对应了中序遍历中「从 左边界 开始到 根节点定位-1」的元素
        root->left = _buildTree(preorder,inorder,pl+1,pl+size_left_subtree,il,iroot-1);
        // 递归地构造右子树，并连接到根节点
        // 先序遍历中「从 左边界+1+左子树节点数目 开始到 右边界」的元素就对应了中序遍历中「从 根节点定位+1 到 右边界」的元素
        root->right = _buildTree(preorder,inorder,pl+size_left_subtree+1,pr,iroot+1,ir);
        return root;
    }
};