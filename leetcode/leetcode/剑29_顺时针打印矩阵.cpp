class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.size() == 0||matrix[0].size() == 0) return {};
        int rows = matrix.size(),cols = matrix[0].size();
        vector<int> order;
        int left = 0,right = cols-1,top =0,bottom = rows -1;
        while(left<=right&&top<=bottom){
            for(int col = left;col<=right;col++){
                order.push_back(matrix[top][col]);
            }
            for(int row = top+1;row<=bottom;row++){
                order.push_back(matrix[row][right]);
            }
            if(left<right && top<bottom){
                for(int col = right -1;col>left;col--){
                    order.push_back(matrix[bottom][col]);
                }
                for(int row = bottom;row>top;row--){
                    order.push_back(matrix[row][left]);
                }
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return order;
    }
};