/*
 * 求一个小数的分数表示，小数表示为 0.A1A2A3...AM(B1B2B3...BN) 括号里面表示无限循环
 * a = A1A2...AM, m = a 的位数，同理 b = B1B2...BN, n = b 的位数
 * 利用几何级数或者直接推导可以得到无限循环小数的分数表示 Y = b / (10^n - 1), 而不循环小数的分数表示为 X = a / 10^m
 * 最后可以求得公式为 [a * (10^n - 1) + b] / [10^m * (10^n - 1)] 
 * 注意：
 * 需要特殊处理 b 或者 n 为 0 的情况
 */
#include <assert.h>

int gcd(int m, int n) {
    int tmp;
    while (n != 0) {
        tmp = m % n;
        m = n;
        n = tmp;
    }
    return m;
}

int power(int x, int k) {
    if (k == 0)
        return 1;
    if ((k & 1) == 1)
        return power(x * x, k / 2) * x;
    return power(x * x, k / 2);
}

void express_float(int a, int m, int b, int n, int *numerator, int *denominator) {
    int power_of_m = power(10, m);
    if (n == 0 || b == 0) {
        *numerator = a;
        *denominator = power_of_m;
    } else {
        int power_of_n = power(10, n);
        *numerator = (power_of_n - 1) * a + b;
        *denominator = power_of_m * (power_of_n - 1);
    }
    int greatest_common_divisor = gcd(*denominator, *numerator);
    *numerator /= greatest_common_divisor;
    *denominator /= greatest_common_divisor;
}

void test_express_float() {
    int numerator, denominator;
    express_float(2, 1, 0, 0, &numerator, &denominator);
    assert(numerator == 1 && denominator == 5);

    express_float(0, 0, 3, 1, &numerator, &denominator);
    assert(numerator == 1 && denominator == 3);

    express_float(5, 1, 3, 1, &numerator, &denominator);
    assert(numerator == 8 && denominator == 15);
}

int main() {
    test_express_float();
}
