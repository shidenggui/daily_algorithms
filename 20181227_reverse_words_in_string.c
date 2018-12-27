void reverse_str(char *start, char *end) {
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

    // move end to last char
    char *end = start;
    while (*end != '\0') end++;
    end--;

    reverse_str(start, end);

    // reverse words
    end = start;
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

    str = (char*)&(char[]){'a', 'b', ' ', '\0'};
    printf("source: '%s'\n", str);
    reverse_words(str);
    printf("reversed: '%s'\n", str);

    str = (char*)&(char[]){'I',' ','a','m',' ','a',' ','s','t','u','d','e','n','t', '.', '\0'};
    printf("source: '%s'\n", str);
    reverse_words(str);
    printf("reversed: '%s'\n", str);
}

int main() {
    test_reverse_words();
}
