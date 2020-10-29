class MedianFinder {
private:
    priority_queue<int,vector<int>,std::less<int>> maxS;
    priority_queue<int,vector<int>,std::greater<int>> minS;
    int size;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        size = 0;
    }
    
    void addNum(int num) {
        size++;
        maxS.push(num);
        minS.push(maxS.top());
        maxS.pop();
        if(maxS.size()<minS.size()){
            maxS.push(minS.top());
            minS.pop();
        }
    }
    
    double findMedian() {
        if(size == 0) return -1;
        if(size % 2) return maxS.top();
        else{
            return (minS.top()+maxS.top())/2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */