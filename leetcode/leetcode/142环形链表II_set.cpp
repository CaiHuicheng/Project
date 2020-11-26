/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> setNode;
        while(head!=nullptr){
            if(setNode.count(head)){
                return head;
            }
            setNode.insert(head);
            head = head->next;
        }
        return nullptr;
    }
};