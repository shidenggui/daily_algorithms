#include <assert.h>

int Gcd(int m, int n) {
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
    if (k & 1)
        return power(x * x, k / 2) * x;
    return power(x * x, k / 2);
}

void express_float(int a, int m, int b, int n, int *x, int *y) {
    int numerator;
    int denominator;

    if (b == 0 || n == 0) {
        numerator = a;
        denominator = power(10, m);
    } else {
        int tmp = power(10, n) - 1;
        numerator = a * tmp + b;
        denominator = power(10, m) * tmp;
    }
    int gcd = Gcd(numerator, denominator);
    *x = numerator / gcd;
    *y = denominator / gcd;
    return;
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

