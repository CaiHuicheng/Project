/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* target = new ListNode(0,head);
        stack<ListNode*> s;
        ListNode* cur = target;
        while(cur){
            s.push(cur);
            cur = cur -> next;
        }
        for(int i =0;i<n;i++){
            s.pop();
        }
        ListNode* prev = s.top();
        prev->next = prev->next->next;
        ListNode* ans = target->next;
        delete target;
        return ans;
    }
};