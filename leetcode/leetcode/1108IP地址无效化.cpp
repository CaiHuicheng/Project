// class Solution {
// public:
    // string defangIPaddr(string address) {
        // string res;
        // for(auto c:address){
            // if(c == '.'){
                // res.append("[.]");
            // }else
                // res.append(1,c);
        // }
        // return res;
    // }
// };
class Solution {
public:
    string defangIPaddr(string address) {
        string res;
        for(auto c:address){
            if(c == '.'){
                res+="[.]";
            }else
                res+=c;
        }
        return res;
    }
};