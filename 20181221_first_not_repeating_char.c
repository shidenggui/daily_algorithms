/*
 * 找到给出的字符串中第一次只出现一次的字符，如果找不到则返回 '\0'
 * 思路：
 * 使用 ASCII_SIZE 大小的数组保存对应的字符数量，类似 radix 排序。
 * 然后第二遍再遍历字符串，返回第一个 cout 为 1 的字符。
 * 如果未找到则返回 '\0'
 */
#include <stdlib.h>
#include <assert.h>
#define ASCII_SIZE (256)

char first_not_repeating_char(char *str) {
    if (str == NULL || *str == '\0')
        return '\0';

    int chars[ASCII_SIZE] = {0};
    for (char *p = str; *p != '\0'; p++)
        chars[*p]++;

    while (*str != '\0') {
        if (chars[*str] == 1)
            return *str;
        str++;
    }
    return '\0';
}

void test_first_not_repeating_char() {
    assert(first_not_repeating_char("") == '\0');
    assert(first_not_repeating_char("1") == '1');
    assert(first_not_repeating_char("12") == '1');
    assert(first_not_repeating_char("112") == '2');
    assert(first_not_repeating_char("1122") == '\0');
    assert(first_not_repeating_char("abaccdeff") == 'b');
}

int main () {
    test_first_not_repeating_char();
}
