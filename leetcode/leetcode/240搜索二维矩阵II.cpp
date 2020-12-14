class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0) return false;
        int rows = matrix.size(),cols = matrix[0].size();
        int row = 0,col = cols-1;
        while(row<=rows-1&&col>=0){
            if(target == matrix[row][col]) return true;
            if(target>matrix[row][col]) row++;
            else col--;          
        }
        return false;
    }
};