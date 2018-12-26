/*
 * 翻转给出的字符串，但是不要翻转对应的单词，标点符号同单词字符
 * 思路：
 * 先翻转整个字符串，然后依序翻转对应的单词即可。主要是边界条件的考量
 */
#include <stdlib.h>
#include <stdio.h>

void reverse_str(char *start, char *end) {
    // start, end 是指针地址，可以直接比较大小
    while (start < end) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

void reverse_words(char *str) {
    if (!str || *str == '\0')
        return;

    char *start = str;
    char *end = str;
    while (*end != '\0') end++;
    end--;

    reverse_str(start, end);

    // reverse words
    while (*start != '\0') {
        while (*start == ' ') start++;
        if (*start == '\0')
            return;

        end = start;
        while (*end != ' ' && *end != '\0') end++;
        end--;

        reverse_str(start, end);
        start = end + 1;
    }
}

// solution from book, 感觉这种更好，因为 while 循环的条件比较简洁
void reverse_words2(char *str) {
    if (!str || *str == '\0')
        return;

    char *start = str;

    char *end = str;
    while (*end != '\0') end++;
    end--;

    reverse_str(start, end);

    // reverse words
    start = end = str;
    while (*start != '\0') {
        if (*start == ' ') {
            start++;
            end++;
        } else if (*end == ' ' || *end == '\0') {
            reverse_str(start, end - 1);
            start = end;
        } else {
            end++;
        }
    }
}


void test_reverse_words() {
    char *str;

    str = (char*)&(char[]){' ', ' ', '\0'};
    printf("source: '%s'\n", str);
    reverse_words(str);
    printf("reversed: '%s'\n", str);

    str = (char*)&(char[]){'a', ' ', '\0'};
    printf("source: '%s'\n", str);
    reverse_words(str);
    printf("reversed: '%s'\n", str);

    str = (char*)&(char[]){' ', 'b', '\0'};
    printf("source: '%s'\n", str);
    reverse_words(str);
    printf("reversed: '%s'\n", str);

    str = (char*)&(char[]){'a', 'b', '\0'};
    printf("source: '%s'\n", str);
    reverse_words(str);
    printf("reversed: '%s'\n", str);

    str = (char*)&(char[]){'I',' ','a','m',' ','a',' ','s','t','u','d','e','n','t', '.', '\0'};
    printf("source: '%s'\n", str);
    reverse_words(str);
    printf("reversed: '%s'\n", str);

    printf("\n\nreverse words2:\n");
    str = (char*)&(char[]){' ', ' ', '\0'};
    printf("source: '%s'\n", str);
    reverse_words2(str);
    printf("reversed: '%s'\n", str);

    str = (char*)&(char[]){'a', ' ', '\0'};
    printf("source: '%s'\n", str);
    reverse_words2(str);
    printf("reversed: '%s'\n", str);

    str = (char*)&(char[]){' ', 'b', '\0'};
    printf("source: '%s'\n", str);
    reverse_words2(str);
    printf("reversed: '%s'\n", str);

    str = (char*)&(char[]){'a', 'b', '\0'};
    printf("source: '%s'\n", str);
    reverse_words2(str);
    printf("reversed: '%s'\n", str);

    str = (char*)&(char[]){'I',' ','a','m',' ','a',' ','s','t','u','d','e','n','t', '.', '\0'};
    printf("source: '%s'\n", str);
    reverse_words2(str);
    printf("reversed: '%s'\n", str);
}

int main() {
    test_reverse_words();
}
