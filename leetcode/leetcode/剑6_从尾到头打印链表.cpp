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
    vector<int> reversePrint(ListNode* head) {
        stack<ListNode *> s;
        ListNode* temp = head;
        while(temp){
            s.push(temp);
            temp = temp->next;
        }
        int size = s.size();
        vector<int> v;
        for(int i=0;i<size;i++){
            v.push_back(s.top()->val);
            s.pop();
        }
        return v;
    }
};