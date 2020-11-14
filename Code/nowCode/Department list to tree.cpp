class Solution {
public:
    /**
     * Convert the department list to preorder traversal of the department tree
     * @param departments string字符串二维数组 [["id1", "parentId", "name"]...], there's only one root department with empty parent id.
     * @param departmentsRowLen int departments数组行数
     * @param departmentsColLen int* departments数组列数
     * @return string字符串vector
     */
    //dfs 建树
    vector<string> listToTree(string** departments, int departmentsRowLen, int* departmentsColLen) {
        // write code here
        map<string, string> idToName;
        map<string, set<string>> departTree;
        vector<string> res;
        int root;
    //1.找到根节点 2.建立id到名字的映射
        for (int i = 0; i<departmentsRowLen; ++i)
        {
                idToName[departments[i][0]] = departments[i][2];
                if (departments[i][1]=="")    
                {   
                    root = i;
                }
                departTree[departments[i][2]] = {};

        }
    //找爹，借助map建立多叉树，以set为子节点集合
        for (int i = 0; i < departmentsRowLen; i++)
        {
            if (departments[i][1] != "")        
                departTree[idToName[departments[i][1]]].insert(departments[i][2]);
        }
    // 递归 前序遍历
        preOrder(departments[root][2],departTree,res);
        return res;
    }
    void preOrder(string s, map<string, set<string>>& departTree,vector<string>& res)
    {
        res.push_back(s);
        if (departTree[s].empty()==false)
        {
            for (auto it= departTree[s].begin(); it!= departTree[s].end(); it++)
                {
                    preOrder(*it, departTree, res);
                }
        }
    }
};