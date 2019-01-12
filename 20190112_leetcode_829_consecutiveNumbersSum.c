int consecutive_numbers_sum(int N) {
    int count = 1;

    int xi;
    for (int i = 2;; i++) {
        xi = N - i * (i - 1) / 2;
        if (xi <= 0)
            break;
        if (xi % i == 0)
            count++;
    }
    return count;
}
