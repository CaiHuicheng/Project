class Solution {
private:
    vector<string> res; // 定义全局变量 res，backtrack()就可以少传一个参数
    string s_copy; // 定义全局变量 s_copy，backtrack()就可以少传一个参数
public:
    vector<string> permutation(string s) {
        if(s.empty()){
            return {};
        }
        s_copy = s;
        dfs(0); // 从 s 的第一位开始排列起，所以传了 0
        return res;
    }
    void dfs(int pos){
        if(pos == s_copy.length() - 1){
            res.push_back(s_copy); // 某条路从头排列到尾了，把这条路的结果输入 res
            return;
        }
        unordered_set<char> prune; // 用于剪枝，不能定义为全局，因为每次递归需要创建一个新的 hashset
        for(int i=pos; i<s_copy.length(); ++i){
            if(prune.count(s_copy[i])){
                continue; // 如果是重复的元素，不要再排一次
            }
            prune.insert(s_copy[i]);
            swap(s_copy[i], s_copy[pos]); // 每个诸侯都有暂时做天子（从 i 处到 pos 处）的机会
            dfs(pos + 1); // 开始往下一层递进（当前诸侯需要寻找皇位（pos 处）继承人）
            swap(s_copy[i], s_copy[pos]); // 当前诸侯任期已满，从 pos 处回到 i 处
        }
    }
    void swap(char& c1, char& c2){
        char temp = c1;
        c1 = c2;
        c2 = temp;
    }
};
