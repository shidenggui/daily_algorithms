/*
 * 统计数组中的逆序对。
 * 这里使用归并，可以得出逆序对的数量 f(n) = f(left, mid) + f(mid + 1, right) + merge_pais((left, mid), (mid + 1, right))
 * 关键问题在于 merge pairs 的时候，如果当左侧数字大于右侧时，即满足出现逆序对的条件，在复制右侧数字到 tmp 的同时，pairs 数要加上左侧数字的数量
 * 时间复杂度 O(LogN) 空间复杂度 O(N)
 */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int merge(int *arr, int left, int left_end, int right_end, int *tmp) {
    int pairs = 0;
    int right = left_end + 1;
    int left_idx = left, right_idx = right, tmp_idx = left;
    while (left_idx <= left_end && right_idx <= right_end) {
        if (arr[left_idx] <= arr[right_idx]) {
            tmp[tmp_idx++] = arr[left_idx++];
        } else {
            // 关键点在此，比如 左边剩下 3, 2, 右边剩下 1，则将 1 复制到 tmp 后，pairs 的增加数是左侧剩下的数组数量，这里就是 2
            pairs += left_end - left_idx + 1;
            tmp[tmp_idx++] = arr[right_idx++];
        }
    }

    while (left_idx <= left_end) {
        tmp[tmp_idx++] = arr[left_idx++];
    }
    while (right_idx <= right_end) {
        tmp[tmp_idx++] = arr[right_idx++];
    }

    for (int i = left; i <= right_end; i++) {
        arr[i] = tmp[i];
    }
    return pairs;
}

int inverse_pairs_core(int *arr, int n, int left, int right, int *tmp) {
    if (left == right)
        return 0;
    int mid = left + (right - left) / 2;
    int left_pairs = inverse_pairs_core(arr, mid - left + 1, left, mid, tmp);
    int right_pairs = inverse_pairs_core(arr, right - mid + 1, mid + 1, right, tmp);
    int merge_pairs = merge(arr, left, mid, right, tmp);
    return left_pairs + right_pairs + merge_pairs;
}

int inverse_pairs(int *arr, int n) {
    if (n <= 0 || !arr)
        return 0;

    int tmp[n];
    return inverse_pairs_core(arr, n, 0, n - 1, tmp);
}

void test_inverse_pairs_core() {
    printf("inverse pairs for {1}:%d\n", inverse_pairs((int*)&(int[]){1}, 1));
    printf("inverse pairs for {1, 2}:%d\n", inverse_pairs((int*)&(int[]){1, 2}, 2));
    printf("inverse pairs for {2, 1}:%d\n", inverse_pairs((int*)&(int[]){2, 1}, 2));
    printf("inverse pairs for {3, 2, 1}:%d\n", inverse_pairs((int*)&(int[]){3, 2, 1}, 3));
    printf("inverse pairs for {7, 5, 6, 4}:%d\n", inverse_pairs((int*)&(int[]){7, 5, 6, 4}, 4));
    assert(inverse_pairs((int*)&(int[]){3, 2, 1}, 3) == 3);
    assert(inverse_pairs((int*)&(int[]){3, 1, 2}, 3) == 2);
    assert(inverse_pairs((int*)&(int[]){7, 5, 6, 4}, 4) == 5);
}

int main() {
    test_inverse_pairs_core();
}
