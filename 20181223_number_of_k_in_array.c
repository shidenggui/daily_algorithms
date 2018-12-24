/*
 * 找出给出数组中指定数字出现的次数，如果该数不存在，返回 0
 * 解题思路：
 * 如果数组范围有限，可以考虑 radix sort
 * 如果不限访问，则使用二分搜索，分别实现 get_first_k 和 get_last_k 然后可以使用 last - first + 1 获得个数。
 * 实现 get_first_k 的时候要注意，如果 mid idx 为 0，则返回 0，还有就是 arr[mid -1] != k 时也返回，其余则使得 end = mid - 1，继续在前半部分搜索。
 * get_last_k 同理。
 * 时间复杂度 O(LogN)，空间复杂度 O(1)
 */
#include <assert.h>

int get_first_k(int *arr, int n, int k);
int get_last_k(int *arr, int n, int k);

int get_number_of_k(int *arr, int n, int k) {
    if (!arr || n <= 0)
        return 0;
    int first = get_first_k(arr, n , k);
    if (first < 0)
        return 0;
    int last = get_last_k(arr, n, k);
    return last - first + 1;
}

int get_first_k(int *arr, int n, int k) {
    int start = 0;
    int end = n - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (k < arr[mid]) {
            end = mid - 1;
        } else if (k > arr[mid]) {
            start = mid + 1;
        } else {
            if (mid == 0 || arr[mid - 1] != k)
                return mid;
            end = mid - 1;
        }
    }
    return -1;
}

int get_last_k(int *arr, int n, int k) {
    int start = 0;
    int end = n - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (k < arr[mid]) {
            end = mid - 1;
        } else if (k > arr[mid]) {
            start = mid + 1;
        } else {
            if (mid == end || arr[mid + 1] != k)
                return mid;
            start = mid + 1;
        }
    }
    return - 1;
}

void test_get_number_of_k() {
    assert(get_number_of_k((int*)&(int[]){1}, 1, 1) == 1);
    assert(get_number_of_k((int*)&(int[]){1}, 1, 0) == 0);
    assert(get_number_of_k((int*)&(int[]){1, 2}, 2, 1) == 1);
    assert(get_number_of_k((int*)&(int[]){1, 2, 2}, 3, 2) == 2);
    assert(get_number_of_k((int*)&(int[]){1, 2, 3, 3, 3, 3, 4, 5}, 8, 3) == 4);
}

int main() {
    test_get_number_of_k();
}
