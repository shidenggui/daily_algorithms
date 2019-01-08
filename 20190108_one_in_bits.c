/*
 * 如果 n 比较小的话，可以用查表法，空间复杂度 O(数字大小) 时间复杂度 O(1)
 * 如果 n 较大，则可以利用 x & (x - 1) 会消除最后一个 1 的特性，空间复杂度 O(1) 时间复杂度 O(n 中 1 的数量)
 */
#include <assert.h>

int ones(int n) {
    int count = 0;
    while (n) {
        n &= n - 1;
        count++;
    }
    return count;
}

void test_ones() {
    assert(ones(0) == 0);
    assert(ones(1) == 1);
    assert(ones(2) == 1);
    assert(ones(9) == 2);
    assert(ones(8) == 1);
    assert(ones(-1) == 32);
}

int main() {
    test_ones();
}
