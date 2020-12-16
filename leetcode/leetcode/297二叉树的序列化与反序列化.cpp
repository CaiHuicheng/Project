/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root)  return "";
        ostringstream res;
        queue<TreeNode*> currQ;
        currQ.push(root);
        while(!currQ.empty()){
            TreeNode *node = currQ.front();
            currQ.pop();
            if(node == nullptr) res<<"null ";
            else{
                res <<node->val<<" ";
                currQ.push(node->left);
                currQ.push(node->right);
            }
        }
        return res.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data.empty()) return nullptr;
        istringstream input(data);
        string info;
        vector<TreeNode*> res;
        while(input>>info){
            if(info == "null") res.push_back(nullptr);
            else
                res.push_back(new TreeNode(stoi(info)));
        }
        int pos = 1;
        // 本循环将 res 中的所有元素连起来，变成一棵二叉树
        for(int  i = 0;pos<res.size();i++){
            if(!res[i]) continue;
            res[i]->left = res[pos++];// pos 此时指向左子树，++后指向右子树
            if(pos<res.size()){
                res[i]->right = res[pos++];// pos 此时指向右子树，++后指向下一个节点的左子树
            }
        }
        return res[0];
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));