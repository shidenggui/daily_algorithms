/*
 * testcases 不足，应该考虑一些常见的 testcases
 */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int str_len(char *str) {
    int count = 0;
    while (*str != '\0') {
        str++;
        count++;
    }
    return count;
}

void reverse(char *start, char *end) {
    char tmp;
    while (start < end) {
        tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}
void left_rotate_string(char *str, int k) {
    // 这里需要排除掉 len 为 0 的情况，不然后面 k%= 0 会出错
    //if (!str || k <= 0)
    if (!str || *str == '\0' || k <= 0)
        return;

    int len = str_len(str);
    // 这里报错了，因为 len 可能为 0, 需要在前面排除掉 len 为 0 的情况
    k %= len;
    if (k == 0)
        return;

    reverse(str, str + k - 1);
    reverse(str + k, str + len - 1);
    reverse(str, str + len - 1);
}

bool is_str_equal(char *s1, char *s2) {
    if (s1 == NULL && s2 == NULL)
        return true;
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2)
            return false;
        // 这里也是忘记递增 s1++, s2++，loop invariant，这个是我最常犯的错误了
        s1++;
        s2++;
    }
    if (*s1 == *s2)
        return true;
    return false;
}

void test_left_rotate_string() {
    char str[4] = "abc";
    left_rotate_string(str, 1);
    assert(is_str_equal(str, "bca"));

    char str2[4] = "";
    left_rotate_string(str2, 1);
    assert(is_str_equal(str2, ""));

    char str3[4] = "a";
    left_rotate_string(str3, 8);
    assert(is_str_equal(str3, "a"));

    char str5[100] = "abcdefg";
    left_rotate_string(str5, 2);
    assert(is_str_equal(str5, "cdefgab"));
}

int main() {
    test_left_rotate_string();
}
