void print_number(char *nums) {
    while (*nums == '0') nums++;
    if (*nums == '\0') {
        printf("0\n");
        return;
    }
    printf("%s\n", nums);
}

void print_char_digits(char *nums, int n, int k) {
    if (n == k) {
        print_number(nums);
        return;
    }

    for (int i = 0; i < 10; i++) {
        nums[k] = '0' + i;
        print_char_digits(nums, n, k + 1);
    }
}

void print_n_digits(unsigned n) {
    char nums[n + 1];
    memset(nums, '0', n);
    nums[n] = '\0';
    print_char_digits(nums, n, 0);
}

void test_print_char_digits() {
    int i;
    
    i = 0;
    printf("%d:\n", i);
    print_n_digits(i);

    i = 1;
    printf("%d:\n", i);
    print_n_digits(i);

    i = 2;
    printf("%d:\n", i);
    print_n_digits(i);
}

int main() {
    test_print_char_digits();
}
