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
    ListNode* sortList(ListNode* head) {
        return sortList(head,nullptr);
    }
    ListNode* sortList(ListNode* head,ListNode* tail) {
        if(head == nullptr) return head;
        if(head->next == tail){
            head->next = nullptr;
            return  head;
        }
        ListNode*  slow = head,*fast = head;
        while(fast!=tail){
            fast = fast->next;
            slow = slow->next;
            if(fast!=tail) fast = fast->next;
        }
        ListNode*mid = slow;
        return merge(sortList(head,mid),sortList(mid,tail));
    }

    ListNode* merge(ListNode* list1,ListNode* list2){
        ListNode* head = new ListNode(0);
        ListNode* tail = head,*tmp1 = list1,*tmp2 = list2;
        while(tmp1!=nullptr&&tmp2!=nullptr){
            if(tmp1->val>tmp2->val){
                tail->next = tmp2;
                tmp2 = tmp2->next;
            }else{
                tail->next = tmp1;
                tmp1 = tmp1->next;
            }
            tail = tail->next;
        }
        if(tmp1!=nullptr) tail->next = tmp1;
        if(tmp2!=nullptr) tail->next = tmp2;
        return head->next;
    }
};