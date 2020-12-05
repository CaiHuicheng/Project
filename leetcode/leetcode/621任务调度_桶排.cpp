class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int len=tasks.size();
        vector<int> vec(26);
        for(char c:tasks) ++vec[c-'A'];
        sort(vec.begin(),vec.end(),[](int& x,int&y){return x>y;});
        int cnt=1;
        while(cnt<vec.size()&&vec[cnt]==vec[0]) cnt++;
        return max(len,cnt+(n+1)*(vec[0]-1) );
    }
};