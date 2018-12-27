/*
 * 坐旋转字符串，犯了无数多编程的小错误。
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
        // 一开始忘记递增 start, end。loop invariant，make progress 怎么忘记了
        start++;
        end--;
    }
}

void left_rotate_string(char *str, int k) {
    if (!str || *str == '\0')
        return;
    char *start = str;
    char *end = start;
    int len = 0;
    // 最开始直接使用 end != '\0'，而 end 本身是指针，结果直接溢出了
    while (*end != '\0') {
        end++;
        len++;
    }
    end--;

    k %= len;
    if (k == 0)
        return;

    reverse_str(start, end);
    char *sub_end = end;
    for (int i = 0; i < k; i++) sub_end--;
    reverse_str(start, sub_end);
    reverse_str(++sub_end, end);
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
