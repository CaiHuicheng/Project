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
    bool hasCycle(ListNode *head) {
        ListNode* fastPoint = head,*slowPoint = head;
        while(fastPoint !=nullptr&&fastPoint->next!=nullptr){
            slowPoint = slowPoint->next;
            fastPoint = fastPoint->next->next;
            while(slowPoint == fastPoint){
                return true;
            }
        }
        return false;
    }
};