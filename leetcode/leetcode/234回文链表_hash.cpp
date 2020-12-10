/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    bool isPalindrome(ListNode* head)
    {
        unordered_map<int,int> dic;
        int seed=0;
        ListNode* head_new=head;
        //生成映射
        while(head_new!=NULL)
        {
            if(dic.find(head_new->val)==dic.cend())
            {
                dic[head_new->val]=seed;
                seed++;
            }
            head_new=head_new->next;
        }
        //正反读数比较
        unsigned long long l=0,r=0,h=1;
        while(head!=NULL)
        {
            l=l*seed+dic[head->val];
            r=r+h*dic[head->val];
            h*=seed;
            head=head->next;
        }
        return l==r;
    }
};