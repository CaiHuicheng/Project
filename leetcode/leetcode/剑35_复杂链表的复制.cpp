/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(nullptr == head) return nullptr;
        map<Node*,Node*> map;
        Node *temp = head;
        while(nullptr != temp){
            map[temp] = new Node(temp->val);
            temp = temp->next;
        }
        Node * cur = head;
        while(nullptr != cur){
            map[cur]->next = map[cur->next];
            map[cur]->random = map[cur->random];
            cur = cur->next;
        }
        return map[head];
    }
};