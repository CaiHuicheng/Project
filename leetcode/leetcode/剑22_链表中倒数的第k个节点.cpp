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
    // ListNode* getKthFromEnd(ListNode* head, int k) {
    //     ListNode *tail = head;
    //     vector<ListNode *> res;
    //     while(tail != nullptr){
    //         res.push_back(tail);
    //         tail=tail->next;
    //     }
    //     return res[res.size()-k];
    // }
    ListNode* getKthFromEnd(ListNode* head, int k) {
       if(!head || k == 0)return nullptr;
       ListNode *fast=head,*slow=head;
       for(int i = 1;i<=k-1;++i){
           if(fast->next)fast = fast->next;
           else return nullptr;
       }
       while(fast->next){
           fast = fast->next;
           slow = slow->next;
       }
       return slow;
    }
};