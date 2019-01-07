/*
 * atoi: https://leetcode.com/problems/string-to-integer-atoi/submissions/
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>


bool g_invalid = false;

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

int atoi(char *str) {
    if (!str) {
        g_invalid = true;
        return 0;
    }
    while (*str != '\0' && *str == ' ') str++;
    if (*str == '\0') {
        g_invalid = true;
        return 0;
    }

    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+')
        str++;
    // 需要判断只有 '-' 的情况
    if (!is_number(*str)) {
        g_invalid = true;
        return 0;
    }

    int result = 0;
    int tmp_prod, tmp_add;
    while (is_number(*str)) {
        tmp_prod = result * 10;
        tmp_add = tmp_prod + *str - '0';
        if ((tmp_prod / 10 != result) || tmp_add < 0) {
            g_invalid = true;
            if (sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }
        result = tmp_add;
        str++;
    }
    // 每次都忘记乘以 sign，汗颜，这就是没有跑 test case 导致的，这个习惯很不好
    // return result;
    return result * sign;
} 

void test_atoi() {
    assert(atoi("42") == 42);
    assert(atoi("   -42") == -42);
    assert(atoi("4193 with words") == 4193);
    assert(atoi("words and 987") == 0);
    assert(atoi("-91283472332") == INT_MIN);
    assert(atoi("91283472332") == INT_MAX);
}

int main() {
    test_atoi();
}
