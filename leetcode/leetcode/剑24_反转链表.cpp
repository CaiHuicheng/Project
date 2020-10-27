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
    ListNode* reverseList(ListNode* head) {
        if(nullptr == head || nullptr == head->next) return head;
        // //1、递归
        // ListNode* res = reverseList(head->next);
        // head->next->next = head;
        // head->next = nullptr;
        // return res;
        //2、双指针
        ListNode* cur=nullptr,*pre = head,*t = nullptr;
        while(nullptr!=pre){
            t = pre->next;
            pre->next = cur;
            cur = pre;
            pre = t;
        }
        return cur;
    }
};