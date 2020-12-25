class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        int c = g.size(),n=s.size(),count = 0;
        for(int i=0,j=0;i<c&&j<n;i++,j++){
            while(j<n&&g[i]>s[j]){
                j++;
            }
            if(j<n) count++;
        }
        return count;
    }
};
