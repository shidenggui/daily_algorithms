/*
 * 给出一个整数 x，求其中 1 的个数
 * 思路1: 暴力搜索
 * 因为要考虑负数的情况，所以不能直接将 x 右移，因为此时如果 x 是负数，右移的话是算术右移，会导致左边补 1。
 * 所以初始化 flag = 1，然后将 flag 与 x 做 & 操作，如果结果为 1 说明这一位为 1，然后依次将 flag 左移 1 位，直到 flag 为零为止。
 * 复杂度为 O(w)，w 为 int 的位宽
 *
 * 思路2：利用 x & (x - 1) 可以消除掉 x 中的一个零
 * 为什么？
 * 考虑如下情况，如果 x 中有 1
 * 1. 1 位于 x 的最右边，此时减 1 使得最后一位变为 0，与自己做 & 运算，即等于 x - 1，消除了最后一位 1
 * 2. 1 位于 x 中的第 m 位，此时减去 1，使得第 m 位变为 0，[m + 1:] 变为 1，而原来 x 中 第 m 位的右边本身都是 0，所以可以用来消去 x - 1 中新产生的 1，而 x - 1 中将 m 位变为零，可以用来消去 x 中第 m 位的1，考虑如下例子:
 * ...1000 减一后变为 ...0111，此时 ...1000 & ...0111 即为 ...0000 消去了 ...1000 中的最后一个 1
 * 时间复杂度 O(n) n 为 x 中 1 的个数
 *
 */
#include <assert.h>

int ones_on(int x) {
    int n = 0;
    int flag = 1;
    while (flag) {
        if (x & flag)
            n++;
        flag <<= 1;
    }
    return n;
}

int ones(int x) {
    int n = 0;
    while (x) {
        x &= x - 1;
        n++;
    }
    return n;
}

void test_ones() {
    assert(ones(0) == 0);
    assert(ones(1) == 1);
    assert(ones(2) == 1);
    assert(ones(9) == 2);
    assert(ones(8) == 1);
    assert(ones(-1) == 32);

    assert(ones_on(0) == 0);
    assert(ones_on(1) == 1);
    assert(ones_on(2) == 1);
    assert(ones_on(9) == 2);
    assert(ones_on(8) == 1);
    assert(ones_on(-1) == 32);
}

int main() {
    test_ones();
}
