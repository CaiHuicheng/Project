class Solution {
public:
    string replaceSpace(string s) {
        string str;
        for(auto c:s){
            if(c == ' ') str += "%20";
            else str += c; 
        }
        return str;
    }
};