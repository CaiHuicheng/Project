/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    int maxSum = INT_MIN;

public:
    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
    int maxGain(TreeNode* root){
        if(root == nullptr) return 0;
        int leftGain = max(maxGain(root->left),0);
        int rightGain = max(maxGain(root->right),0);
        int pathSum = root->val+leftGain+rightGain;
        maxSum = max(maxSum,pathSum);
        return root->val+max(leftGain,rightGain);
    }
    
};