/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        if( nullptr == pHead) return nullptr;
        ListNode* head = nullptr,*p = pHead,*q = nullptr;
        while(nullptr != p){
            q = p->next;
            p->next = head;
            head = p;
            p = q;
        }
        return head;
    }
};