/*
 * 求解字符串 s1 变动 到 s2 的距离
 * 思路: 设计一个递归函数，假设返回的结果是两个子串的距离。
 * basecases: 如果 s1 为空或者 s2 为空，则返回对应的不为空的子串的长度。 
 * 如果两个子串第一个字符相同，直接比较下一个字符。
 * 如果不同，则我们有以下三种方式处理:
 *  1. 删除 s1 的第一个字符，然后继续与 s2 比较
 *  2. 删除 s2 的第一个字符，然后继续与 s1 比较。
 *  3. 将 s1，s2 的字符变得相同，然后继续比较下一个字符。
 *  这三种方式都会使得 distance + 1
 */
#include <assert.h>
#include <stdlib.h>

int str_len(char *s) {
    if (!s)
        return 0;
    int count = 0;
    for (; *s != '\0'; s++)
        count++;
    return count;
}

int max2(int a, int b) {
    return a > b? a: b;
}

int min3(int a, int b, int c) {
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    return c;
}

// 会有子串重复计算的问题，可以通过添加对 str 的 idx 的索引来记录计算过的结果
// leetcode 上会超时，因为 f(n) = 3 f(n - 1) => O(3^N) 这个确实有点夸张，看来不存储中间结果是不行了
int dis(char *s1, char *s2) {
    if (!s1 || !s2 || *s1 == '\0' || *s1 == '\0') 
        return max2(str_len(s1), str_len(s2));

    if (*s1 == *s2)
        return dis(s1 + 1, s2 + 1);
    return min3(dis(s1 + 1, s2), dis(s1, s2 + 1), dis(s1 + 1, s2 + 1)) + 1;
}

void test_dis() {
    assert(dis(NULL, NULL) == 0);
    assert(dis("", NULL) == 0);
    assert(dis("", "") == 0);
    assert(dis("a", "") == 1);
    assert(dis("a", "b") == 1);
    assert(dis("a", "ba") == 1);
    assert(dis("abcdefg", "abcdef") == 1);
    assert(dis("horse", "ros") == 3);
}

int main() {
    test_dis();
}
