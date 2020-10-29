class MinStack {
private:
    stack<int> s;
    stack<int> mins;
public:
    /** initialize your data structure here. */
    MinStack() {

    }
    
    void push(int x) {
        s.push(x);
        if(mins.empty()||mins.top()>x)mins.push(x);
        else if(!mins.empty()) mins.push(mins.top());
    }
    
    void pop() {
        mins.pop();
        s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int min() {
        return mins.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */