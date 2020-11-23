class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.size() == 0||matrix[0].size() == 0) return {};
        vector<int> res;
        int rows = matrix.size(),cols = matrix[0].size();
        int left = 0, right = cols - 1, top = 0, bottom = rows - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; column++) {
                res.push_back(matrix[top][column]);
            }
            for (int row = top + 1; row <= bottom; row++) {
                res.push_back(matrix[row][right]);
            }
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) {
                    res.push_back(matrix[bottom][column]);
                }
                for (int row = bottom; row > top; row--) {
                    res.push_back(matrix[row][left]);
                }
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return res;
    }
};
};