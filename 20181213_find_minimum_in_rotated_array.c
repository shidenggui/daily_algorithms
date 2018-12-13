/*
 * 旋转数组指的是讲一个排序数组的前某 x 个数，移动到数组末尾。
 * 现在要求求该旋转数组中的最小数？
 * 思路：
 * 如果把数的大小设想成柱状图的话，则前半部分递增数组以及后半部分递增数组都是梯形，而且前半部分梯形的左边比后半部分的梯形的右边要高。
 * 1. 另 start 为 0， end 为 n - 1
 * 2. 这时候取中间值 center，如果 arr[center] <= arr[end] 的话，则说明 arr[center] 属于后半部分梯形，更新 start = center，反之更新 end = center
 * 3. 当 end - start <= 1 时停止，因为这时 start 属于前半部分梯形的最后一个，而 end 属于后半部分梯形的第一个值，也即是最小值，返回 arr[end] 即可
 * 考虑额外两种特殊情况
 * 1. 如果旋转了 0 个数，即数组不变，此时判断 arr[0] < arr[n - 1] 即可，若为 true，直接返回 arr[n - 1]
 * 2. 如果 arr[start] == arr[center] == arr[right]，此时无法确定 center 属于哪一部分梯形，直接变为 brute search
 * 复杂度：
 * 平均 Log(N) 最差 O(N)
*/ 
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void error(char *msg) {
    printf("error: %s\n", msg);
    exit(1);
}

int brute_search(int *arr, int n) {
    int min_value = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value)
            min_value = arr[i];
    }
    return min_value;
}
int find_minimum(int *arr, int n) {
    if (arr == NULL || n <= 0)
        error("invalid input");
    if (arr[0] < arr[n - 1])
        return arr[0];

    int start = 0;
    int end = n - 1;
    int center;
    while (end - start > 1) {
        center = start + (end - start) / 2;
        if (arr[center] == arr[start] && arr[center] == arr[end])
            return brute_search(arr + start, end - start + 1);
        if (arr[center] <= arr[end])
            end = center;
        else
            start = center;
    }

    return arr[end];
}

void test_find_minimum() {
    int arr[] = {3, 4, 5, 1, 2};
    assert(find_minimum(arr, 5) == 1);

    int arr2[] = {1, 0, 1, 1, 1};
    assert(find_minimum(arr2, 5) == 0);

    int arr3[] = {1, 1, 1, 0, 1};
    assert(find_minimum(arr3, 5) == 0);

    int arr4[] = {0, 1};
    assert(find_minimum(arr4, 2) == 0);

    int arr5[] = {1, 0};
    assert(find_minimum(arr5, 2) == 0);
}

int main() {
    test_find_minimum();
}


