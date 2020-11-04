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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ans = nullptr;
        for(auto list:lists)
            ans = mergeTwoLists(ans,list);
        return ans;
    }
    ListNode* mergeTwoLists(ListNode* ans,ListNode* list){
        if(!ans||!list) return ans?ans:list;
        ListNode head,*tail = &head,*aPtr = ans,*lPtr = list;
        while(aPtr&&lPtr){
            if(aPtr->val >= lPtr->val){
                tail->next = lPtr;
                lPtr = lPtr->next;
            }else{
                tail->next = aPtr;
                aPtr = aPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr?aPtr:lPtr);
        return head.next;
    }
};