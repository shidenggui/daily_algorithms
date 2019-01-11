/*
 * https://leetcode.com/problems/string-to-integer-atoi/submissions/
 */
int g_invalid = false;

bool is_number(char c) {
    return c >= '0' && c <= '9';
}

int myAtoi(char* str) {
    if (!str) {
        g_invalid = true;
        return 0;
    }    
    
    // skip spaces
    while (*str != '\0' && *str == ' ') str++;
    if (*str == '\0') {
        g_invalid = true;
        return 0;
    }
    
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
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
            return INT_MIN;
        }
        result = tmp_add;
        str++;
    }
    return result * sign;
}
