class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
		ListNode thead=ListNode(-1);
		thead.next=head;
		ListNode *pre,*cur;
		int t;
		cur=&thead;
		while (cur){
			pre = cur;
			cur = cur->next;
			while (cur && cur->next && 
					cur->next->val==cur->val){
				t=cur->val;
				while (cur && cur->val==t)
					cur=cur->next;		
			}
			pre->next=cur;
		}
		return thead.next;
    }
};