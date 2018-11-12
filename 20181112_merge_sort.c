#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

// arrsize for int
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(int))

void merge(int *arr, int left_start, int right_start, int right_end, int *tmp) {
    // for assign
    int tmp_start = left_start;
    // for copy
    int tmp_init = left_start;
    int left_end = right_start - 1;
    while (left_start <= left_end && right_start <= right_end) {
        if (arr[left_start] < arr[right_start])
            tmp[tmp_start++] = arr[left_start++];
        else
            tmp[tmp_start++] = arr[right_start++];
    }
    while (left_start <= left_end)
        tmp[tmp_start++] = arr[left_start++];
    while (right_start <= right_end)
        tmp[tmp_start++] = arr[right_start++];

    // copy elelements from tmp to arr
    while (tmp_init <= right_end) {
        arr[tmp_init] = tmp[tmp_init];
        tmp_init++;
    }
}

void msort(int *arr, int left, int right, int *tmp) {
    if (left == right)
        return;

    int center = left + (right - left) / 2;
    msort(arr, left, center, tmp);
    msort(arr, center + 1, right, tmp);
    merge(arr, left, center + 1, right, tmp);
}

// driver
void merge_sort(int *arr, int n) {
    if (n <= 1)
        return;
    int *tmp = malloc(sizeof(int) * n);
    msort(arr, 0, n - 1, tmp);
}


bool is_same_arr(int *a1, int *a2, int n) {
    for (int i = 0; i < n; i++) {
        if (a1[i] != a2[i])
            return false;
    }
    return true;
}

void print_arr(int *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void test_sort() {
    int arr[] = {1};
    merge_sort(arr,  ARR_SIZE(arr));
    print_arr(arr, ARR_SIZE(arr));
    assert(is_same_arr(arr, (int []){1}, ARR_SIZE(arr)));

    int arr2[] = {1, 0};
    merge_sort(arr2, ARR_SIZE(arr2));
    print_arr(arr2, ARR_SIZE(arr2));
    assert(is_same_arr(arr2, (int []){0, 1}, ARR_SIZE(arr2)));

    int arr3[] = {2, 1, 0};
    merge_sort(arr3, ARR_SIZE(arr3));
    print_arr(arr3, ARR_SIZE(arr3));
    assert(is_same_arr(arr3, (int []){0, 1, 2}, ARR_SIZE(arr3)));

    int arr4[] = {9, 6, 2, 3, 1, 2};
    merge_sort(arr4, ARR_SIZE(arr4));
    print_arr(arr4, ARR_SIZE(arr4));
    assert(is_same_arr(arr4, (int []){1, 2, 2, 3, 6, 9}, ARR_SIZE(arr4)));

    int arr5[] = {2, 2, 2};
    merge_sort(arr5, ARR_SIZE(arr5));
    print_arr(arr5, ARR_SIZE(arr5));
    assert(is_same_arr(arr5, (int []){2, 2, 2}, ARR_SIZE(arr5)));
}

int main() {
    test_sort();
}
