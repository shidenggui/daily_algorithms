int count_digit(int n, int k) {
    int count = 0;

    int remain = n;
    int base = 1;
    int current;
    while (remain > 0) {
        current = remain % 10;
        // prev
        remain /= 10;
        count += remain * base;
        if (current > k)
            count += base;
        // 这里是 current == k, 因为 current < k 时不需要增加 count
        // else
        else if (current == k)
            count += n % base + 1;
        base *= 10;
    }
    return count;
}

int countDigitOne(int n) {
    return count_digit(n, 1);
}
