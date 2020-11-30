class BIT{
private:
    vector<int> tree;
    int n;
public:
    BIT(int _n):n(_n),tree(_n+1){}
    static constexpr int lowbit(int x){
        return x&(-x);
    }
    void update(int x,int d){
        while(x<=n){
            tree[x] += d;
            x += lowbit(x);
        }
    }
    int query(int x) const{
        int ans = 0;
        while(x){
            ans += tree[x];
            x-=lowbit(x);
        }
        return ans;
    }
};

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        set<long long> allNumbers;
        for(auto x:nums){
            allNumbers.insert(x);
            allNumbers.insert((long long)x*2);
        }
        unordered_map<long long,int> values;
        int index = 0;
        for(auto x:allNumbers){
            values[x] = ++index;
        }
        int ret = 0;
        BIT bit(values.size());
        for(int i = 0;i<nums.size();i++){
            int left = values[(long long)nums[i] * 2], right = values.size();
            ret += bit.query(right) - bit.query(left);
            bit.update(values[nums[i]], 1);
        }
        return ret;
    }
};