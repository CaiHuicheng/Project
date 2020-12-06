class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        // 初始结点为空
        head = nullptr;
    }
    void push(int x) {
        if(head==nullptr){
            // 两步走 
            // 1.新建结点 最小值为入栈结点值 新结点指向head  
            // 2.head移动到新结点
            head = new ListNode(x,x,head);
        }else{
            // 最小值为 入栈结点值和之前结点最小值的min
            head = new ListNode(x,min(x,head->min),head);
        }
    }
    void pop() {
        // 删除末端
        ListNode* p = head;
        head = head->next;
        delete p;
    }
    int top() {
        return head->val;
    }
    int getMin() {
        return head->min;
    }
private:
    // 声明链表结构
    struct ListNode{
        int val;
        int min;
        ListNode* next;
        ListNode():val(0),min(0),next(nullptr){}
        ListNode(int _val,int _min, ListNode* _next):val(_val),min(_min),
        next(_next){}
    };
    // 初始结点
    ListNode* head;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */