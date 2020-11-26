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
        if(head == nullptr||head->next==nullptr) return nullptr;
        ListNode *slow = head,*fast = head->next;
        while(slow!=fast){
            slow = slow->next;
            if(fast==nullptr||fast->next==nullptr) return nullptr;
            fast = fast->next->next;
            if(fast == slow) break;
        }
        fast = head;
        while(fast!=slow){
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};