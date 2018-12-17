#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print(char *num) {
    while (*num == '0') num++;
    if (*num == '\0') {
        printf("0\n");
        return;
    }

    printf("%s\n", num);
}

void print_number_recursively(char *num, unsigned n,  unsigned k) {
    if (k == n) {
        print(num);
        return;
    }
    for (int i = 0; i < 10; i++) {
        num[k] = i + '0';
        print_number_recursively(num, n, k + 1);
    }
}

void print_number(unsigned n) {
    char num[n + 1];
    memset(num, '0', n);
    num[n] = '\0';
    print_number_recursively(num, n, 0);
}

void test_print_number() {
    printf("n: 0\n");
    print_number(0);

    printf("n: 1\n");
    print_number(1);

    printf("n: 2\n");
    print_number(2);
}

int main() {
    test_print_number();
}
