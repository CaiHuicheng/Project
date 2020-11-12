class Solution {
public:
 /*
        [1 2 3]
        [4 5 6]
        [7 8 9] 
        1、矩阵逆置
        [1 4 7]
        [2 5 8]
        [3 6 9] 
        2、第i列 和第 n-1-i列交换 （i=0 开始），且j<n/2)
        [7 4 1]
        [8 5 2]
        [9 6 3]
        */
    void rotate(vector<vector<int>>& matrix) {
       int n = matrix.size();
       for(int i =0;i<n;i++){
           for(int j =i;j<n;j++){
               swap(matrix[i][j],matrix[j][i]);
           }
       }
       for(int i=0;i<n;i++){
           for(int j =0;j<n/2;j++){
               swap(matrix[i][j],matrix[i][n-1-j]);
           }
       }
    }
};