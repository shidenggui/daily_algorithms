/*
 * atoi: https://leetcode.com/problems/string-to-integer-atoi/submissions/
 */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

int atoi(char *str) {
    if (!str)
        return 0;

    char *ptr = str;
    while (*ptr != '\0' && *ptr == ' ') ptr++;
    if (*ptr == '\0')
        return 0;

    int sign = 1;
    if (*ptr == '-') {
        sign = -1;
        ptr++;
    } else if (*ptr == '+') {
        ptr++;
    }

    int result = 0;
    while (is_number(*ptr)) {
        // 这里溢出可能有两种，一种是乘法溢出，一种是加法溢出
        int tmp = result * 10;
        int tmp_add = tmp + *ptr - '0';
        if ((tmp / 10 != result) || tmp_add < 0) {
            if (sign == 1)
                return INT_MAX;
            return INT_MIN;
        }
        result = tmp_add;
        ptr++;
    }
    // 不要忘记乘以 sign
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
