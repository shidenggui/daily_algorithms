#include <stdlib.h>
#include <assert.h>

int find_split_flag(int *arr, int n) {
    int remain = 0;
    for (int i = 0; i < n; i++)
        remain ^= arr[i];
    int flag = 1;
    while ((flag & remain) != flag) flag <<= 1;
    return flag;
}

void find_number_appear_once(int *arr, int n, int *n1, int *n2) {
    *n1 = 0;
    *n2 = 0;
    int flag = find_split_flag(arr, n);
    for (int i = 0; i < n; i++) {
        if ((arr[i] & flag) == flag)
            *n1 ^= arr[i];
        else
            *n2 ^= arr[i];
    }
}

void test_find_number_appear_once() {
    int n1 = 0, n2 = 0;
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
