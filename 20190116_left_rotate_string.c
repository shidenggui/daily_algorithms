#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

int str_len(char *s) {
    int count = 0;
    for (; *s != '\0'; s++)
        count++;
    return count;
}
void reverse(char *start, char *end) {
    char tmp;
    for(; start < end; start++, end--) {
        tmp = *start;
        *start = *end;
        *end = tmp;
    }
}
void left_rotate_string(char *s, int k) {
    // 这里要判断 *s 是否长度为 0，否则后面 len 为 0，% 会出错，果然，没有测试用例运行的话，
    // 凭经验果然不行，如果不严格执行 check list 这种错误难以杜绝
    // 以后一定要测试用例，不管怎样，不然只是一次次在同一个错误中跌倒
    if (!s || *s == '\0')
        return;

    int len = str_len(s);
    k %= len;
    if (k == 0)
        return;

    reverse(s, s + k - 1);
    reverse(s + k, s + len - 1);
    reverse(s, s + len - 1);
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
