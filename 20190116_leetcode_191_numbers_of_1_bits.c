/*
 * 利用 n & (n - 1) 会消去最后一个 0 的特性
 */

int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) {
        n &= n - 1;
        count++;
    }
    return count;
}
