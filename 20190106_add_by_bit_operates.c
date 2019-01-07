#include <assert.h>

int add(int n1, int n2) {
    int sum;
    // 因为 sum + carry 很可能还是会溢出，所以需要循环到 carry == 0 为止
    while (n2 != 0) {
        // sum 保存了 n1 + n2 但是不进位的结果
        sum = n1 ^ n2;
        // n2 保存了 n1 + n2 的所有进位
        n2 = (n1 & n2) << 1;
        n1 = sum;
    }
    return n1;
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
