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
        return merge(lists,0,lists.size()-1);
    }

    ListNode* merge(vector<ListNode*> & lists,int l,int r){
        if(l==r) return lists[l];
        if(l>r) return nullptr;
        int mid = (l+r)>>1;
        return mergeTwoLists(merge(lists,l,mid),merge(lists,mid+1,r));
    }

    ListNode* mergeTwoLists(ListNode* ans,ListNode* list){
        if(!ans||!list) return ans?ans:list;
        ListNode *head = new ListNode();
        ListNode *tail =head,*aPtr = ans,*lPtr = list;
        while(aPtr&&lPtr){
            if(aPtr->val > lPtr->val){
                tail->next = lPtr;
                lPtr = lPtr->next;
            }else{
                tail->next = aPtr;
                aPtr = aPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr?aPtr:lPtr);
        return head->next;
    }
};