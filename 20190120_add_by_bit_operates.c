#include <assert.h>
int add(int a, int b) {
    int sum_without_carry;
    while (b != 0) {
        sum_without_carry = a ^ b;
        b = (a & b) << 1;
        a = sum_without_carry;
    }
    return a;
}

void test_add() {
    assert(add(1, 3) == 4);
    assert(add(17, 5) == 22);
    assert(add(17, 15) == 32);
    assert(add(-1, -3) == -4);
    assert(add(-10, 3) == -7);
    assert(add(10, -14) == -4);
}

int main() {
    test_add();
}
