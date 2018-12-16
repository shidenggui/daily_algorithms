/*
 * 输入 n，顺时针打印从 0 开始的 n * n 矩阵
 * 这里跟输入 m, n 的矩阵，顺时针打印比较大的区别在于，最后只有两种可能，一种是只有一个，即只有向右打印。令一种是四个正方形，只有向右，向下，向左
 * 所以向下打印，则一定会向左打印，则向左打印的判断可以省略。
 * 先把所有数字收集到一个矩形中，在打印出来。这样时间，空间复杂度都需要 O(N^2)，而实际上我只需要直到 (i, j) 坐标的值即可，空间复杂度可以为 O(1)，就是不知道对应的公式是什么?
 */
#include <stdlib.h>
#include <stdio.h>

void print_matrix(unsigned n) {
    int matrix[n][n];
    int count = 0;
    for (int start = 0; start * 2 < n; start++) {
        int end_i = n - start;
        int end_j = n - start;
        for (int j = start; j < end_j; j++) {
            matrix[start][j] = count++;
        }

        if (start + 1 >= end_i)
            break;
        for (int i = start + 1; i < end_i; i++) {
            matrix[i][end_j - 1] = count++;
        }

        for (int j = end_j - 2; j >= start; j--) {
            matrix[end_i - 1][j] = count++;
        }

        if (end_i - 2 <= start)
            break;
        for (int i = end_i - 2; i > start; i--) {
            matrix[i][start] = count++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%-3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int test_print_matrix() {
    printf("\n1 * 1:\n");
    print_matrix(1);

    printf("\n2 * 2:\n");
    print_matrix(2);

    printf("\n3 * 3:\n");
    print_matrix(3);

    printf("\n4 * 4:\n");
    print_matrix(4);

    printf("\n5 * 5:\n");
    print_matrix(5);
}

int main() {
    test_print_matrix();
}
