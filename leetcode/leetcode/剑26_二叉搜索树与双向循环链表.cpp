/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
private:
    Node *head,*tail;
public:
    Node* treeToDoublyList(Node* root) {
        if(nullptr == root) return nullptr;
        inorder(root);
        head->left = tail;
        tail->right = head;
        return head;
    }
    void inorder(Node* root){
        if(nullptr == root) return ;
        inorder(root->left);
        if(!tail){
            head = root;
        }else{
            tail->right = root;
            root->left = tail;
        }
        tail = root;
        inorder(root->right);
    }
};