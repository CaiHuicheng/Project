class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> map;
        stack<int> st;
        for(auto num:nums2){
            while(!st.empty()&&st.top()<num){
                map[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }
        while(!st.empty()){
            map[st.top()] = -1;
            st.pop();
        }

        vector<int>ans;
        for(auto num:nums1){
            ans.push_back(map[num]);
        }
        return ans;
    }
};