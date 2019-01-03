#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

int split_flag(int *arr, int n) {
    int remain = 0;
    for (int i = 0; i < n; i++)
        remain ^= arr[i];

    // 想到一种更快的方法 (x & x - 1) 可以消去最后一个 1，
    // 然后直接 x ^ (x & x - 1) 就可以拿到最后一个为 1 的 flag
    return remain ^ (remain & (remain - 1));
}

bool find_number_appear_once(int *arr, int n, int *n1, int *n2) {
    if (!arr || n < 2)
        return false;

    int flag = split_flag(arr, n);
    *n1 = 0;
    *n2 = 0;
    for (int i = 0; i < n; i++) {
        if ((arr[i] & flag) == flag)
            *n1 ^= arr[i];
        else
            *n2 ^= arr[i];
    }
    return true;
}

void test_find_number_appear_once() {
    int n1 = 0, n2 = 0;
    find_number_appear_once((int*)&(int[]){1, 2, 3, 3}, 4, &n1, &n2);
    assert(n1 == 1);
    assert(n2 == 2);

    n1 = 0, n2 = 0;
    find_number_appear_once((int*)&(int[]){2,4,3,6,3,2,5,5}, 8, &n1, &n2);
    assert(n1 == 6);
    assert(n2 == 4);
    
    n1 = 0, n2 = 0;
    find_number_appear_once((int*)&(int[]){2,9,3,7,3,2,5,5}, 8, &n1, &n2);
    assert(n1 == 7);
    assert(n2 == 9);
}

int main() {
    test_find_number_appear_once();
}
