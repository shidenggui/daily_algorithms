/* 
 * 著名的约瑟夫环问题。这次总算看懂了，
 * 最后递推公式的推导见书 P228 第四十五题
 * 时间复杂度 O(N), 空间复杂度 O(1)
 */
#include <assert.h>

int last_remain(int n, int k) {
    int remain = 0;
    for (int i = 2; i <= n; i++) {
        remain = (remain + k) % i;
    }
    return remain;
}

void test_last_remain() {
    assert(last_remain(5, 3) == 3);
    assert(last_remain(4, 3) == 0);
}

int main() {
    test_last_remain();
}
