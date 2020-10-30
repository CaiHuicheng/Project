/*
 * 回溯法
 *
 * 字符串的排列和数字的排列都属于回溯的经典问题
 *
 * 回溯算法框架：解决一个问题，实际上就是一个决策树的遍历过程：
 * 1. 路径：做出的选择
 * 2. 选择列表：当前可以做的选择
 * 3. 结束条件：到达决策树底层，无法再做选择的条件
 *
 * 伪代码：
 * result = []
 * def backtrack(路径，选择列表):
 *     if 满足结束条件：
 *         result.add(路径)
 *         return
 *     for 选择 in 选择列表:
 *         做选择
 *         backtrack(路径，选择列表)
 *         撤销选择
 *
 * 核心是for循环中的递归，在递归调用之前“做选择”，
 * 在递归调用之后“撤销选择”。
 *
 * 字符串的排列可以抽象为一棵决策树：
 *                       [ ]
 *          [a]          [b]         [c]
 *      [ab]   [ac]  [bc]   [ba]  [ca]  [cb]
 *     [abc]  [acb] [bca]  [bac]  [cab] [cba]
 *
 * 考虑字符重复情况：
 *                       [ ]
 *          [a]          [a]         [c]
 *      [aa]   [ac]  [ac]   [aa]  [ca]  [ca]
 *     [aac]  [aca] [aca]  [aac]  [caa] [caa]
 *
 * 字符串在做排列时，等于从a字符开始，对决策树进行遍历，
 * "a"就是路径，"b""c"是"a"的选择列表，"ab"和"ac"就是做出的选择，
 * “结束条件”是遍历到树的底层，此处为选择列表为空。
 *
 * 本题定义backtrack函数像一个指针，在树上遍历，
 * 同时维护每个点的属性，每当走到树的底层，其“路径”就是一个全排列。
 * 当字符出现重复，且重复位置不一定时，需要先对字符串进行排序，
 * 再对字符串进行“去重”处理，之后按照回溯框架即可。
 * */
 class Solution {
public:
    vector<string> permutation(string s) {
        if(s.empty()) return {};
        std::sort(s.begin(),s.end());
        std::vector<std::string> res;
        //标记字符是否遍历过
        std::vector<bool> visit(s.size(),false);
        std::string track;
        backtrack(res,s,track,visit);

        return res;
    }
    void backtrack(std::vector<std::string> &res,std::string s,std::string &track,std::vector<bool>visit){
        //回溯结束条件
        if(track.size() == s.size()){
            res.push_back(track);
            return ;
        }
        //选择
        for(int i = 0;i<s.size();i++){
            //排除不合法选项
            if(visit[i]){
                continue;
            }
            if(i>0&&!visit[i-1]&&s[i-1] == s[i]){
                continue;
            }
            visit[i] = true;
            //做选择
            track.push_back(s[i]);
            //进入下一次决策树
            backtrack(res,s,track,visit);
            //撤销选择
            track.pop_back();
            visit[i] = false;
        }
    }
};