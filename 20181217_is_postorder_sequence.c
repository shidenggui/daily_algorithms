/*
 * 判断是否是二叉搜索树的后序遍历序列
 * 利用了一下的两个性质
 * 1. 后序遍历时，生成的序列依次为左子树序列，右子树序列加上最后的 root 值
 * 2. 二叉搜索树的左子树小于 root，右子树大于 root
 * 解题思路：递归
 * 1. base cases; 当 arr 为 NULL 或者 n 小于等于 0 时，返回 true
 * 2. 找到右子树的起点，然后遍历右子树，如果右子树有值小于 root，则返回 true
 * 3. 递归检查左右子树是否都满足后序遍历的性质 
 */
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

bool is_postorder_sequence(int *arr, int n) {
    if (arr == NULL || n <= 0)
        return true;

    int root = arr[n - 1];
    int i = 0;
    while (i < n - 1 && arr[i] < root) i++;
    for (int j = i; j < n - 1; j++) {
        if (arr[j] < root)
            return false;
    }
    return is_postorder_sequence(arr, i) && is_postorder_sequence(arr + i, n - 1 - i);
}

void test_is_postorder_sequence() {
    assert(is_postorder_sequence((int*)&(int[]){0}, 1) == true);
    assert(is_postorder_sequence((int*)&(int[]){0, 1}, 2) == true);
    assert(is_postorder_sequence((int*)&(int[]){2, 1}, 2) == true);

    assert(is_postorder_sequence((int*)&(int[]){5, 7, 6, 9, 11, 10, 8}, 7));
    assert(is_postorder_sequence((int*)&(int[]){7, 4, 6, 5}, 4) == false);
}

int main() {
    test_is_postorder_sequence();
}
