// https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/
// 在 leetcode 的时候，插入排序忘记 j-- 了
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define CUTOFF (3)

bool g_invalid = false;
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insert_sort(int *arr, int n) {
    int tmp, j;
    for (int i = 1; i < n; i++) {
        tmp = arr[i];
        for (j = i; j > 0 && arr[j - 1] > tmp; j--)
            arr[j] = arr[j - 1];
        arr[j] = tmp;
    }
}

int median3(int *arr, int left, int right) {
    int mid = left + (right - left) / 2;
    if (arr[left] > arr[mid])
        swap(&arr[left], &arr[mid]);
    if (arr[mid] > arr[right])
        swap(&arr[mid], &arr[right]);
    if (arr[left] > arr[mid])
        swap(&arr[left], &arr[mid]);
    swap(&arr[mid], &arr[right - 1]);
    return arr[right - 1];
}

void q_sort(int *arr, int left, int right, int k) {
    if (right - left < CUTOFF) {
        insert_sort(arr + left, right - left + 1);
        return;
    }
    int pivot = median3(arr, left, right);
    int i, j;
    for (i = left + 1, j = right - 2;; i++, j--) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i >= j)
            break;
        swap(&arr[i], &arr[j]);
    }
    swap(&arr[i], &arr[right - 1]);
    if (k - 1 < i)
        q_sort(arr, left, i - 1, k);
    else if (k - 1 > i)
        q_sort(arr, i + 1, right, k);
}

int quick_select(int *arr, int n, int k) {
    if (!arr || n <= 0 || k > n || k < 1) {
        g_invalid = true;
        return 0;
    }
    q_sort(arr, 0, n - 1, k);
    return arr[k - 1];
}

void test_quick_select() {
    int *arr = (int*)(int[]){5, 4, 3, 2, 1};
    assert(quick_select(arr, 5, 1) == 1);
    assert(quick_select(arr, 5, 2) == 2);
    assert(quick_select(arr, 5, 3) == 3);
    assert(quick_select(arr, 5, 4) == 4);
    assert(quick_select(arr, 5, 5) == 5);

    arr = (int*)(int[]){2, 1, 5, 4, 3};
    assert(quick_select(arr, 5, 1) == 1);
    assert(quick_select(arr, 5, 2) == 2);
    assert(quick_select(arr, 5, 3) == 3);
    assert(quick_select(arr, 5, 4) == 4);
    assert(quick_select(arr, 5, 5) == 5);
}

int main() {
    test_quick_select();
}
