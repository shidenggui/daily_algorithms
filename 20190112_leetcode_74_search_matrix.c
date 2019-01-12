// https://leetcode.com/problems/search-a-2d-matrix/
bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    // 这里 i 是从 0 开始 到 <= RowSize - 1，我最开始写成了 i = RowSize -1 到 i >= 0 
    // 幸好基于 loop invariant 和 testcase 检查了下，才纠正过来
    // 这里就看出 testcases 的重要性了，很多小错误都可以一遍 check 出来
    for (int i = 0, j = matrixColSize - 1; i <= matrixRowSize - 1 && j >= 0;) {
        if (target > matrix[i][j])
            i++;
        else if (target < matrix[i][j])
            j--;
        else
            return true;
    }
    return false;
}
