/*
 * 求 N! 用二进制表示时的 trailing zeros
 * 这里有个非常巧妙的算法。使用 N - one_bits(N) 即为结果。
 * 具体可以通过等比数列的求和公式得出，具体等我有空写篇文章。
 * 数学真是优美。
 */
#include <assert.h>
int zeros(int n) {
    int count = 0;
    while (n != 0) {
        n &= n - 1;
        count++;
    }
    return n - count;
}

void test_zeros(int n) {
    assert(zeros(0) == 0);
    assert(zeros(1) == 0);
    assert(zeros(2) == 1);
    assert(zeros(3) == 1);
    assert(zeros(4) == 3);
}

int main() {
    test_zeros();
}
