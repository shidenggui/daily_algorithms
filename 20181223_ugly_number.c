/*
 * 计算 nth 个丑数，丑数即质因数只有2、3、5的数，同时习惯上将 1 作为第一个丑数
 * 解题思路:
 * 其实是一道动态规划的题目
 * f(n) = min(f(t2) * 2, f(t3) * 3, f(t5) * 5)
 * 第 n 个丑数必然由第 t2 个数乘以 2 得到或者第 t3 个数乘以 3 或者第 t5 个数乘以 5 得到。
 * 而关键就是怎么获取到 t2, t3, t5 的值。
 * 他们有以下属性：
 * 1. f(t2) * 2, f(t3) * 3, f(t5) * 5) 比 f(n - 1) 要大
 * 2. f(t2 - 1) * 2 要比 f(n) 要小，其他同理
 * 这样的话我们可以通过获取到 f(n) 之后，循环累加对应的 t2、t3、t5 直到找到比 f(n) 大为止的数
 */
#include <assert.h>
#include <stdio.h>

int min3(int a, int b, int c) {
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    return c;
}

int ugly_number(int n) {
    if (n <= 0)
        return 0;
    int nums[n];
    nums[0] = 1;
    int t2 = 0, t3 = 0, t5 = 0;
    for (int i = 1; i < n; i++) {
        nums[i] = min3(nums[t2] * 2, nums[t3] * 3, nums[t5] * 5);
        while (nums[t2] * 2 <= nums[i]) t2++;
        while (nums[t3] * 3 <= nums[i]) t3++;
        while (nums[t5] * 5 <= nums[i]) t5++;
    }
    return nums[n - 1];
}

void test_ugly_number() {
    for (int i = 1; i < 11; i++) {
        printf("%d: %d\n", i, ugly_number(i));
    }
    assert(ugly_number(0) == 0);
    assert(ugly_number(1) == 1);
    assert(ugly_number(2) == 2);
    assert(ugly_number(3) == 3);
    assert(ugly_number(4) == 4);
    assert(ugly_number(5) == 5);
    assert(ugly_number(6) == 6);
    assert(ugly_number(7) == 8);
    assert(ugly_number(8) == 9);
    assert(ugly_number(9) == 10);
    assert(ugly_number(10) == 12);
}

int main() {
    test_ugly_number();
}
