/*
 * 顺时针打印 m *n 的矩阵 matrix，非常绕的一道题目，具体分析如下
 * 1. 每一圈打印的起始位置，如下思考
 * 每打印一圈，如果还有下一圈的话，则假设已经打印了 k 圈，下一圈的起始位置为 start_i, start_j，则该点的上侧肯定打印了 k 层，左侧也打印了 k 层，所以起始位置应该为 start_i 和 start_j 应该都为 k。
 * 而且存在 k 的前提时上侧和左侧都有 k 层可供打印，既然这样的话以行的层数探讨，k * 2 代表已经打印的上下两侧的 k * 2，在加上当前最新开始的一层即，m >= k * 2 + 1 才能满足可以打印第 k + 1层，
 * 而 m >= k * 2 + 1 ==> m - 1 >= k * 2 ==> m > k * 2 ==> k * 2 < m，同理 k * 2 < n
 * 2. 需要打印的矩形区域，假设开始打印的位置为 (start, start)，则结束位置的外面一层为为 (m - start, n - start)，思考 2 * 2 的矩阵即可，起始为 (0, 0) 末尾为 (2 - 0, 2 - 0) = (2, 2)
 * 下面是打印时每一方向的考量，需要注意的时，如果不满足该方向的打印条件，则直接 break，打印结束
 * 令 (i, j) 为需要打印的坐标
 * 3. 向右打印, 行不变，列变, 从 (start, start) 开始向右， j = start, j < end_j, j++ 而行即为开始的 start，matrix 坐标为 (start * n + j)
 * 4. 向下打印，列不变，行变。因为向右打印导致打印需要从下一行开始，所以从 (start + 1, end_j - 1)，而且要保证 (start + 1 < end_i) , i = start + 1, i < end_i, i++，matrix 坐标为 (i * n + end_j - 1)
 * 5. 向左打印，行不变，列变。因为向下打印导致打印的列需要向左挪动一列，所以从 (end_i - 1, end_j - 2)，而且要保证 (end_j - 2 >= start) , j = end_j - 2, j >= start, j--，matrix 坐标为 ((end_i - 1) * n + j)
 * 5. 向上打印，列不变，行变。因为之前的打印，所以最开始的 start 那一行不需要打印了，所以从 (end_i - 2, start)，而且要保证 (end_j - 2 > start) , i = end_i - 2, i > start, i--，matrix 坐标为 (i * n + start)
 * 
 */
#include <stdlib.h>
#include <stdio.h>

void print_matrix_clockwise(int *matrix, int m, int n) {
    if (matrix == NULL) {
        return;
    }

    for (int start = 0; start * 2 < m && start * 2 < n; start++) {
        int end_i = m - start;
        int end_j = n - start;

        for (int j = start; j < end_j; j++) {
            printf("%d ", matrix[start * n + j]);
        }

        if (start + 1 >= end_i)
            break;
        for (int i = start + 1; i < end_i; i++) {
            printf("%d ", matrix[i * n + end_j - 1]);
        }

        if (end_j - 2 < start)
            break;
        for (int j = end_j - 2; j >= start; j--) {
            printf("%d ", matrix[(end_i - 1) * n + j]);
        }

        if (end_i - 2 <= start)
            break;
        for (int i = end_i - 2; i > start; i--) {
            printf("%d ", matrix[i * n + start]);
        }
    }
    printf("\n");
}

void test_print_matrix_clockwise() {
    int *matrix;
    matrix = (int*)&(int[][1]){{1}};
    print_matrix_clockwise(matrix, 1, 1);
    printf("should be 1\n");

    matrix = (int*)&(int[][2]){{1, 2}};
    print_matrix_clockwise(matrix, 1, 2);
    printf("should be 1 2\n");

    printf("last rec, only left, down, down left:\n");
    matrix = (int*)&(int[][4]){{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    print_matrix_clockwise(matrix, 4, 4);
    printf("should be 1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10\n");

    printf("last rec, only left:\n");
    matrix = (int*)&(int[][3]){{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    print_matrix_clockwise(matrix, 3, 3);
    printf("should be 1 2 3 6 9 8 7 4 5\n");

    printf("last rec, only left, down:\n");
    matrix = (int*)&(int[][3]){{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    print_matrix_clockwise(matrix, 4, 3);
    printf("should be 1 2 3 6 9 12 11 10 7 4 5 8\n");

    printf("last rec, left, down, down left, up:\n");
    matrix = (int*)&(int[][4]){{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}, {17, 18, 19, 20}};
    print_matrix_clockwise(matrix, 5, 4);
    printf("should be 1 2 3 4 8 12 16 20 19 18 17 13 9 5 6 7 11 15 14 10\n");

}

int main() {
    test_print_matrix_clockwise();
}
