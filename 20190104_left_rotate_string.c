/*
 * 判断字符串是否结束应该用 *str == '\0' 而不是 str
 * 这是非常容易犯的一个关于字符串的小错误
 */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void reverse_str(char *start, char *end) {
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

int str_len(char *str) {
    int len = 0;
    // 出错点，char * 取值应该用 *str
    // while (str != '\0') {
    while (*str != '\0') {
        str++;
        len++;
    }
    return len;
}

void left_rotate_string(char *str, int k) {
    if (!str || *str == '\0' || k <= 0)
        return;
    int len = str_len(str);
    k %= len;
    if (k <= 0)
        return;

    reverse_str(str, str + k - 1);
    reverse_str(str + k, str + len - 1);
    reverse_str(str, str + len - 1);
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
