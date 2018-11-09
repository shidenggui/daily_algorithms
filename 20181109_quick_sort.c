#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#define CUTOFF (15)

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int median3(int *arr, int left, int right) {
    // avoid overflow
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

void insertion_sort(int *arr, int n) {
    int inserted, j;
    for (int i = 1; i < n; i++) {
        inserted = arr[i];
        for (j = i; j > 0 && arr[j - 1] > inserted; j--)
            arr[j] = arr[j - 1];
        arr[j] = inserted;
    }
}

void q_sort(int *arr, int left, int right) {
    if (CUTOFF > right - left) {
        insertion_sort(arr, right - left + 1);
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
    // restore pivot
    swap(&arr[i], &arr[right - 1]);

    q_sort(arr, left, i - 1);
    q_sort(arr, i + 1, right);
}

// driver
void quick_sort(int *arr, int n) {
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
