class Solution {
public:
    char firstUniqChar(string s) {
        // unordered_map<char,bool> map;
        // for(auto c:s){
        //     map[c]= (map.find(c) == map.end());
        // }
        // for(auto c:s){
        //     if(map[c]) return c;
        // }
        // return ' ';
        vector<char>keys;
        unordered_map<char,bool> map;
        for(auto c:s){
            if(map.find(c) == map.end()) keys.push_back(c);
            map[c] = map.find(c) == map.end();
        }
        for(auto c:keys){
            if(map[c]) return c;
        }
        return ' ';
    }
};