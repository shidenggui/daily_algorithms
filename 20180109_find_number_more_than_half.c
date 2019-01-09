/*
 * 找出在数组中超过一半的数。
 * 比quick select 更快，而且时间复杂度保证 O(N)，空间复杂度保证 O(1)
 */
#include <assert.h>

int more_than_half(int *arr, int n) {
    if (!arr || n <= 0)
        return -1;
    int target = arr[0];
    int times = 1;
    for (int i = 1; i < n; i++) {
        if (times != 0) {
            if (target == arr[i])
                times++;
            else
                times--;
        } else {
            target = arr[i];
            times = 1;
        }
    }
    return target;
}

void test_more_than_half() {
    assert(more_than_half((int*)&(int[]){1}, 1) == 1);
    assert(more_than_half((int*)&(int[]){1, 1, 2}, 3) == 1);
    assert(more_than_half((int*)&(int[]){2, 2, 1}, 3) == 2);
    assert(more_than_half((int*)&(int[]){2, 1, 2}, 3) == 2);
}

int main() {
    test_more_than_half();
}
