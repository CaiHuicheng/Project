class Solution {
private:
    int rows, cols;
    vector<vector<int>> DIRECTIONS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    // 当前结点的父亲结点
    vector<int> parent;
    // 以当前结点为根结点的子树的结点总数
    vector<int> nums;

    // 二维坐标转换为一维坐标
    int getIndex(int x, int y) {
        return x * cols + y;
    }

    // 路径压缩，只要求每个不相交集合的「根结点」的子树包含的结点总数数值正确即可，因此在路径压缩的过程中不用维护数组 size
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) {
            return;
        }
        parent[rootX] = rootY;
        // 在合并的时候维护数组 size
        nums[rootY] += nums[rootX];
    }
    
    // 在并查集的根结点的子树包含的结点总数
    int getSize(int x) {
        int root = find(x);
        return nums[root];
    }
    
    // 输入坐标在二维网格中是否越界
    bool inArea(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        rows = grid.size();
        cols = grid[0].size();
        // 第 1 步：把 grid 中的砖头全部击碎，通常算法问题不能修改输入数据，这一步非必需，可以认为是一种答题规范
        vector<vector<int>> copy(grid);
        // 把 copy 中的砖头全部击碎
        for (auto& hit : hits) {
            copy[hit[0]][hit[1]] = 0;
        }
        // 第 2 步：建图，把砖块和砖块的连接关系输入并查集，size 表示二维网格的大小，也表示虚拟的「屋顶」在并查集中的编号
        int size = rows * cols;
        for (int i = 0; i <= size; ++i) {
            parent.push_back(i);
            nums.push_back(1);
        }
        // 将下标为 0 的这一行的砖块与「屋顶」相连
        for (int i = 0; i < cols; ++i) {
            if (1 == copy[0][i]) {
                Union(i, size);
            }
        }
        // 其余网格，如果是砖块向上、向左看一下，如果也是砖块，在并查集中进行合并
        for (int i = 1; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (1 == copy[i][j]) {
                    // 如果上方也是砖块
                    if (1 == copy[i - 1][j]) {
                        Union(getIndex(i - 1, j), getIndex(i, j));
                    }
                    // 如果左边也是砖块
                    if (j > 0 && 1 == copy[i][j - 1]) {
                        Union(getIndex(i, j - 1), getIndex(i, j));
                    }
                }
            }
        }
        // 第 3 步：按照 hits 的逆序，在 copy 中补回砖块，把每一次因为补回砖块而与屋顶相连的砖块的增量记录到 res 数组中
        int hitsLen = hits.size();
        vector<int> res(hitsLen);
        for (int i = hitsLen - 1; i >= 0; --i) {
            int x = hits[i][0];
            int y = hits[i][1];
            // 逆向补回的时候，与屋顶相连的砖块数量也肯定不会增加
            if (0 == grid[x][y]) {
                continue;
            }
            // 补回之前与屋顶相连的砖块数
            int origin = getSize(size);
            // 注意：如果补回的这个结点在第 1 行，要告诉并查集它与屋顶相连（逻辑同第 2 步）
            if (0 == x) {
                Union(y, size);
            }
            // 在 4 个方向上看一下，如果相邻的 4 个方向有砖块，合并它们
            for (auto& direction : DIRECTIONS) {
                int newX = x + direction[0];
                int newY = y + direction[1];
                if (inArea(newX, newY) && 1 == copy[newX][newY]) {
                    Union(getIndex(x, y), getIndex(newX, newY));
                }
            }
            // 补回之后与屋顶相连的砖块数
            int current = getSize(size);
            // 减去的 1 是逆向补回的砖块（正向移除的砖块），与 0 比较大小，是因为存在一种情况，添加当前砖块，不会使得与屋顶连接的砖块数更多
            res[i] = max(0, current - origin - 1);
            // 真正补上这个砖块
            copy[x][y] = 1;
        }
        return res;
    }
};