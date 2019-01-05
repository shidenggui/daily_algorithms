/*
 * https://leetcode.com/problems/ugly-number-ii/
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
    
    int t2, t3, t5;
    t2 = t3 = t5 = 0;
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
