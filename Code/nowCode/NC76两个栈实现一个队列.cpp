class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int tail;
        if(!stack2.empty()){
            tail = stack2.top();stack2.pop();
            return tail;
        }
        if(stack1.empty()&&stack2.empty()){
            return -1;
        }
        while(!stack1.empty()){
            stack2.push(stack1.top());
            stack1.pop();
        }
        tail = stack2.top();stack2.pop();
        return tail;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};