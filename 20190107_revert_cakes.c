/*
 * 翻烙饼问题，只允许从顶上选择一定的烙饼数翻转，最后把整个烙饼堆按从小到大排序。
 * 先找到最大的烙饼，然后翻转顶部到最大的烙饼，把最大的烙饼翻到顶上，然后再翻转整个烙饼堆，将最大的烙饼翻转到下面。然后递归这个过程直到只剩下一张烙饼为止。
 */
#include <stdlib.h>
#include <stdio.h>

void print_arr(int *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void revert(int *arr, int left, int right) {
    while (left < right) {
        int tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;

        left++;
        right--;
    }
}

int arr_size = 0;

void revert_cakes_core(int *arr, int n) {
    if (n == 1)
        return;
    int max_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[max_idx])
            max_idx = i;
    }

    // 先翻转把最大的翻转到顶上
    revert(arr, 0, max_idx);
    // 然后再翻转整个数组把最大的翻转到最下面
    // 我一开始写成了翻转后面的，那这样就毫无意义了，只是重复翻转来翻转去
    //revert(arr, max_idx + 1, n - 1);
    revert(arr, 0, n - 1);
    printf("revert %d ~ %d, %d ~ %d\n", 0, max_idx, max_idx + 1, n - 1);
    print_arr(arr, arr_size);
    revert_cakes_core(arr, n - 1);
}

void revert_cakes(int *arr, int n) {
    if (!arr || n <= 1)
        return;
    revert_cakes_core(arr, n);
}

void test_revert_cakes() {
    printf("revert 1, 2, 4, 3:\n");
    arr_size = 4;
    revert_cakes((int*)&(int[]){1, 2, 4, 3}, 4);

    printf("\nrevert 1, 2, 4, 3:\n");
    arr_size = 10;
    revert_cakes((int*)&(int[]){3,2,1,6,5,4,9,8,7,0}, 10);
}

int main() {
    test_revert_cakes();
}
