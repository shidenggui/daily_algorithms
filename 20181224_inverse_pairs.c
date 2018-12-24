#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int merge(int *arr, int left, int left_end, int right_end, int *tmp) {
    int right = left_end + 1;
    int left_idx = left, tmp_idx = left;
    int right_idx = right;
    int pairs = 0;
    while (left_idx <= left_end && right_idx <= right_end) {
        if (arr[left_idx] <= arr[right_idx])
            tmp[tmp_idx++] = arr[left_idx++];
        else {
            pairs += left_end - left_idx + 1;
            tmp[tmp_idx++] = arr[right_idx++];
        }
    }
    while (left_idx <= left_end)
        tmp[tmp_idx++] = arr[left_idx++];
    while (right_idx <= right_end)
        tmp[tmp_idx++] = arr[right_idx++];
    for (int i = left; i <= right_end; i++)
        arr[i] = tmp[i];
    return pairs;
}

int inverse_pairs_core(int *arr, int left, int right, int *tmp) {
    if (left == right)
        return 0;
    int mid = left + (right - left) / 2;
    int left_pairs = inverse_pairs_core(arr, left, mid, tmp);
    int right_pairs = inverse_pairs_core(arr, mid + 1, right, tmp);
    int merge_pairs = merge(arr, left, mid, right, tmp);
    return left_pairs + right_pairs + merge_pairs;
}

int inverse_pairs(int *arr, int n) {
    if (!arr || n <= 1)
        return 0;

    int tmp[n];
    return inverse_pairs_core(arr, 0, n - 1, tmp);
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
