#include <assert.h>

int add(int n1, int n2) {
    int tmp;

    // 这里 n1, n2 可能为负数，因为 int 类型正负数的加减法在 bit 上都是同样的
    // 所以循环到 n2 != 0 为止，如果 n2 > 0 就无法处理附属的情况了
    // while (n2 > 0) {
    while (n2 != 0) {
        tmp = n1 ^ n2;
        n2 = (n1 & n2) << 1;
        n1 = tmp;
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
