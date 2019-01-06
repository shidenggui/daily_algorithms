#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

// 实际情况中 CUTOFF 取 15 到 20 之间
#define CUTOFF (3)
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void insert_sort(int *arr, int n) {
    int tmp;
    for (int i = 1; i < n; i++) {
        tmp = arr[i];
        int j;
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

void q_sort(int *arr, int left, int right) {
    if (right - left < CUTOFF) {
        // 排序数组的开头是 arr + left
        //insert_sort(arr, right - left + 1);
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

    q_sort(arr, left, i - 1);
    q_sort(arr, i + 1, right);
}

void quick_sort(int *arr, int n) {
    if (!arr || n < 2)
        return;
    q_sort(arr, 0, n - 1);
}

void print_arr(int *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void test_sort() {
    int arr[] = {1};
    quick_sort(arr, sizeof(arr) / sizeof(int));
    print_arr(arr, sizeof(arr) / sizeof(int));
    int arr2[] = {1, 0};
    quick_sort(arr2, sizeof(arr2) / sizeof(int));
    print_arr(arr2, sizeof(arr2) / sizeof(int));
    int arr3[] = {2, 1, 0};
    quick_sort(arr3, sizeof(arr3) / sizeof(int));
    print_arr(arr3, sizeof(arr3) / sizeof(int));
    int arr4[] = {9, 6, 2, 3, 1, 2};
    quick_sort(arr4, sizeof(arr4) / sizeof(int));
    print_arr(arr4, sizeof(arr4) / sizeof(int));
    int arr5[] = {2, 2, 2};
    quick_sort(arr5, sizeof(arr5) / sizeof(int));
    print_arr(arr5, sizeof(arr5) / sizeof(int));
}

int main() {
    test_sort();
}
