class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<int,vector<string>> dp;
        unsigned int t,y;
        for(auto &s:strs){
            t = 1;
            y = 0;
            for(char &c:s){
                t*=c;
                y+=c;
            }
            dp[t+y].push_back(s);
        }
        for(auto &m:dp){
            res.push_back(m.second);
        }
        return res;
    }
    // 利用质数表  建立映射关系的 HashMap 求解
    // vector<vector<string>> groupAnagrams(vector<string>& strs) {
    // vector<vector<string>> res;
    // unordered_map<double,vector<string>> occ;
    // // 100以内25个质数 再加一个即可构建质数表
    // map<char,double> primeNum= {
    //     {'a',2.0},{'b',3.0},{'c',5.0},{'d',7.0},{'e',11.0},{'f',13.0},{'g',17.0},
    //     {'h',19.0},{'i',23.0},{'j',29.0},{'k',31.0},{'l',37.0},{'m',41.0},
    //     {'n',43.0},{'o',47.0},{'p',53.0},{'q',59.0},{'r',61.0},{'s',67.0},
    //     {'t',71.0},{'u',73.0},{'v',79.0},{'w',83.0},{'x',89.0},{'y',97.0},{'z',101.0}
    // };
    // for(auto &str:strs){
    //     double val=1.0;
    //     for(auto &vacabulary:str){
    //         val*=primeNum[vacabulary];
    //     }
    //     occ[val].push_back(str);
    // }
    // for(auto &oc:occ){
    //     res.push_back(oc.second);
    // }
    // return res;
    // }
};