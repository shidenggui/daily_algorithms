#include <assert.h>
#include <stdbool.h>

int find_k(int *arr, int n, int k, bool find_first) {
    if (!arr || n < 0)
        return -1;
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (k < arr[mid])
            right = mid - 1;
        else if (k > arr[mid])
            left = mid + 1;
        else {
            if (find_first) {
                if (mid == 0 || arr[mid - 1] != k)
                    return mid;
                right = mid - 1;
            } else {
                // 判断不等于 k 才能确定已经是 last 了
                // if (mid == right || arr[mid + 1] == k)
                if (mid == right || arr[mid + 1] != k)
                    return mid;
                left = mid + 1;
            }
        }
    }
    return -1;
}

int get_number_of_k(int *arr, int n, int k) {
    if (!arr || n < 1)
        return 0;

    const bool find_first = true;
    int first = find_k(arr, n, k, find_first);
    if (first == -1)
        return 0;

    const bool find_last = false;
    int last = find_k(arr + first, n - first, k, find_last);
    // 因为 last 是从 arr + first 开始搜索的，所以返回的 last 就是以 k 开头的数字的最长的下标，而个数就是 last + 1;
    // 而不是原来的 first - last + 1;
    // return last - first + 1;
    return last + 1;
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
