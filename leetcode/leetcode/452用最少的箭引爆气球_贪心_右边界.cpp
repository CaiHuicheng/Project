class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        sort(points.begin(),points.end(),[](const vector<int>& u, const vector<int>& v){
            return u[1]<v[1];
        });
        int pos = points[0][1];
        int ans = 1;
        for(const vector<int>& b:points){
            if(b[0]>pos){
                pos = b[1];
                ++ans;
            }
        }
        return ans;
    }
};