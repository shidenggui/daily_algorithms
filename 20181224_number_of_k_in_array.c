#include <assert.h>

int search_first_k(int *arr, int n, int k) {
    int start = 0;
    int end = n - 1;
    while (start <= end) {
        // 这里竟然写成 int center = left + (right - left) / 2
        // 实在汗颜，把二分搜索的直接搬过来了
        int center = start + (end - start) / 2;
        if (k < arr[center]) {
            end = center - 1;
        } else if (k > arr[center]) {
            start = center + 1;
        } else {
            if (center == 0 || arr[center - 1] != k)
                return center;
            end = center - 1;
        }
    }
    return -1;
}

int search_last_k(int *arr, int n, int k) {
    int start = 0;
    int end = n - 1;
    while (start <= end) {
        int center = start + (end - start) / 2;
        if (k < arr[center]) {
            end = center - 1;
        } else if (k > arr[center]) {
            start = center + 1;
        } else {
            if (center == end || arr[center + 1] != k)
                return center;
            start = center + 1;
        }
    }
    return -1;
}

int get_number_of_k(int *arr, int n, int k) {
    if (!arr || n <= 0)
        return 0;
    int first = search_first_k(arr, n, k);
    if (first < 0)
        return 0;
    int last = search_last_k(arr, n, k);
    return last - first + 1;
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
