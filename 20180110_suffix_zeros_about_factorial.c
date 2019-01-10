#include <assert.h>
#include <stdio.h>

int zeros(int n) {
    int count = 0;
    while (n != 0) {
        n /= 5;
        count += n;
    }
    return count;
}

long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return result;
}

void test_zeros() {
    printf("factorial for 0: %lld\n", factorial(0));
    assert(zeros(0) == 0);
    printf("factorial for 1: %lld\n", factorial(1));
    assert(zeros(1) == 0);
    printf("factorial for 5 for 5: %lld\n", factorial(5));
    assert(zeros(5) == 1);
    printf("factorial for 10: %lld\n", factorial(10));
    assert(zeros(10) == 2);
    printf("factorial for 24: %lld\n", factorial(24));
    // 溢出了
    assert(zeros(24) == 4);
    printf("factorial for 25: %lld\n", factorial(25));
    assert(zeros(25) == 6);
}

int main() {
    test_zeros();
}


