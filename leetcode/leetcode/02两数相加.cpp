/*
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

*/

#include<iostream>
#include<list>

using namespace std;


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//创建新list 求和
//获取两个链表所对应的长度
//在较短的链表末尾补零
//对齐相加考虑进位
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		int value_temp = 0;
		int co = 0;
		ListNode* p = NULL;
		while (l1 != NULL || l2 != NULL) {
			if (l1 == NULL) {
				l1 = new ListNode(0);
			}
			else if (l2 == NULL) {
				l2 = new ListNode(0);
			}
			value_temp = l1->val + l2->val + co;
			co = (value_temp >= 10 ? 1 : 0);
			p->next = new ListNode(value_temp % 10);
			p = p->next;
			l1 = l1->next;
			l2 = l2->next;
		}
		if (co == 1) {
			p->next = new ListNode(1);
		}
		return p->next;
	}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode *head = nullptr, *tail = nullptr;
		int carry = 0;
		while (l1 || l2) {
			int n1 = l1 ? l1->val : 0;
			int n2 = l2 ? l2->val : 0;
			int sum = n1 + n2 + carry;
			if (!head) {
				head = tail = new ListNode(sum % 10);
			}
			else {
				tail->next = new ListNode(sum % 10);
				tail = tail->next;
			}
			carry = sum / 10;
			if (l1) {
				l1 = l1->next;
			}
			if (l2) {
				l2 = l2->next;
			}
		}
		if (carry > 0) {
			tail->next = new ListNode(carry);
		}
		return head;
	}
};

int main() {

	system("pause");
	return 0;
}