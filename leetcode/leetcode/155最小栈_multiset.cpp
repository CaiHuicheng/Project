class MinStack {
public:
    /** initialize your data structure here. */
    MinStack()=default;//默认初始化
    
    inline void push(int x) {
        s1.push(x);//两个容器同时加入新元素
        s2.insert(x);
    }
    
    inline void pop() {
        auto temp=s1.top();//记录此时的栈顶元素
        s1.pop();//栈顶元素出栈
        s2.erase((s2.equal_range(temp)).first);//equal_range函数返回一个迭代器pair，表示s2中等于栈顶元素的范围，
                                               //因为如果此时栈顶的元素在s2中有多个，直接执行erase(temp)会删除所有的
                                               //等于此元素的元素，这不是我们希望的，所以用了上述的函数来删除第一个等于
                                               //栈顶元素的元素
    }
    
    inline int top() {
        return s1.top();
    }
    
    inline int getMin() {
        return *s2.begin();//第一个元素即为最小
    }
private:
    stack<int> s1;
    multiset<int> s2;//可重复容器,用来存储要入栈的值，multiset容器会自动从小到大排序，所以最小元素就是s2的一个元素
};