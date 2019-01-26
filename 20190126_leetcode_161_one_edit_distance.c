/*
 * Ques tion: Given two strings S  and T, determine if they are both one edit distance apart
 * 思路：
 * 只有三种可能：
 * 如果两个字符串长度之间大于 1，不可能为 1 edit distance，return false
 * 如果为 1，则两个字符串前面都应该相同，只有最后一个字符串不同
 * 如果为 0，则中间应该只有一个字符串不同，其他都相同
 */
#include <assert.h>
#include <stdbool.h>

int str_len(char *s) {
    if (!s)
        return 0;
    int count = 0;
    for (; *s != '\0'; s++)
        count++;
    return count;
}

bool one_edit_distance(char *s1, char *s2) {
    if (!s1 || !s2)
        return false;
    int m = str_len(s1);
    int n = str_len(s2);
    if (m > n) return one_edit_distance(s2, s1);
    if (n - m >= 2) return false;

    int i = 0;
    while (i < m && s1[i] == s2[i]) i++;
    // 如果较短的字符与较长的字符串完全相同，则在 m != n 时 edit disntance 为 1，否则为 0
    // 所以返回 m != n
    if (i == m) return m != n;

    // 这里如果 m != n 起始可以直接返回 false
    // 因为中间已经有一个字符串不同，而 m != n 暗示着两个字符串的长度差 1，那已经不可能是 1 edit distance了
    // 不过这里如果只在 m == n 时递增也是一样的。
    // 不过考虑下面那种感觉更加简洁，即将 if (m == n) i++ 变成 
    // if (m != n)
    //     return false;
    // i++;
    if (m == n) i++;
    while (i < m && s1[i] == s2[i]) i++;
    return i == m;
}

bool one_edit_distance2(char *s1, char *s2) {
    if (!s1 || !s2)
        return false;
    int m = str_len(s1);
    int n = str_len(s2);
    if (m > n) return one_edit_distance(s2, s1);
    if (n - m >= 2) return false;

    int i = 0;
    while (i < m && s1[i] == s2[i]) i++;
    // 如果较短的字符与较长的字符串完全相同，则在 m != n 时 edit disntance 为 1，否则为 0
    // 所以返回 m != n
    if (i == m) return m != n;

    // 这里如果 m != n 起始可以直接返回 false
    // 因为中间已经有一个字符串不同，而 m != n 暗示着两个字符串的长度差 1，那已经不可能是 1 edit distance了
    // 不过这里如果只在 m == n 时递增也是一样的。
    // 不过考虑下面那种感觉更加简洁，即将 if (m == n) i++ 变成 
    // if (m != n)
    //     return false;
    // i++;
    if (m != n) return false;
    i++;
    while (i < m && s1[i] == s2[i]) i++;
    return i == m;
}

void test_one_edit_distance() {
    assert(one_edit_distance("", "") == false);
    assert(one_edit_distance("a", "") == true);
    assert(one_edit_distance("aa", "aab") == true);
    assert(one_edit_distance("aba", "aab") == false);
    assert(one_edit_distance("aba", "ada") == true);

    assert(one_edit_distance2("", "") == false);
    assert(one_edit_distance2("a", "") == true);
    assert(one_edit_distance2("aa", "aab") == true);
    assert(one_edit_distance2("ba", "aab") == false);
    assert(one_edit_distance2("aba", "ada") == true);
}

int main() {
    test_one_edit_distance();
}
