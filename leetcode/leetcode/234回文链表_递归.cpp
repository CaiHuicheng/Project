/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    ListNode* frontPointer;
public:
    bool isPalindrome(ListNode* head) {
       frontPointer = head;
       return recursivelyCheck(head);
    }

    bool recursivelyCheck(ListNode* head){
        if(head != nullptr){
            if(!recursivelyCheck(head->next)) return false;
            if(head->val != frontPointer->val) return false;
            frontPointer = frontPointer->next;
        }
        return true;
    }
};