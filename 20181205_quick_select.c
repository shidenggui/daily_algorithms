#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define CUTOFF (3)

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertion_sort(int *arr, int n) {
    int tmp, j;
    for (int i = 1; i < n; i++) {
        tmp = arr[i];
        for (j = i; j > 0 && arr[j - 1] > tmp; j--)
            arr[j] = arr[j - 1];
        arr[j] = tmp;
    }
}

int median3(int *arr, int left, int right) {
    int center = left + (right - left) / 2;
    if (arr[left] > arr[center])
        swap(&arr[left], &arr[center]);
    if (arr[center] > arr[right])
        swap(&arr[center], &arr[right]);
    if (arr[left] > arr[center])
        swap(&arr[left], &arr[center]);
    swap(&arr[center], &arr[right - 1]);
    return arr[right - 1];
}

int q_select(int *arr, int left, int right, int k) {
    if (right - left + 1 <= CUTOFF) {
        insertion_sort(arr + left, right - left + 1);
        return arr[k - 1];
    }
    int pivot = median3(arr, left, right);
    int i = left + 1;
    int j = right - 2;
    while (true) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i >= j)
            break;
        swap(&arr[i], &arr[j]);
        i++;
        j--;
    }
    swap(&arr[i], &arr[right - 1]);
    if (k - 1 < i)
        return q_select(arr, left, i - 1, k);
    if (k - 1 > i)
        return q_select(arr, i + 1, right, k);
    return arr[i];
}
// driver for q_select
// arr contains at least one element and k is legal
int quick_select(int *arr, int n, int k) {
    return q_select(arr, 0, n - 1, k);
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
