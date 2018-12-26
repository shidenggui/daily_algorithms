/*
 * 给出一个数，打印出和为 k 的连续正数序列。
 * 类似在递增数组中找到两个值使得对应的和为指定值。
 * 使用一个 small 和 big 指针，然后一个 sum 记录 [small, sum] 区间的和的变更，根据 sum 的值移动指针，然后抱着 big <= (k / 2 + 1) 同时 small < big 即可。
 * 测试用例：
 * k = 2,
 * k = 3,
 * k = 5
 *
 */
void print_sequence(int start, int end) {
    while (start <= end) {
        printf("%d ", start);
        start++;
    }
    printf("\n");
}

void find_series_with_sum(int k) {
    int small = 1, big = 2;
    int sum = small + big;
    int end = k / 2 + 1;

    // 这里 big <= end  而且需要额外判断 small < big，不然考虑 k 为 2 的情况，如果没有 small < big 就会打印出 2
    while (small < big && big <= end) {
        if (sum < k) {
            sum += ++big;
        } else if (sum > k) {
            // 这里的 sum 是减去 small 增加之前的值，而不是当 sum < k 时增加 big 增加后的值
            sum -= small++;
        } else {
            // 打印序列后要记得增加 big 的值和对应的 sum
            print_sequence(small, big);
            sum += ++big;
        }
    }
}

void test_find_series_with_sum() {
    int i;

    i = 1;
    printf("sum: %d\n", i);
    find_series_with_sum(i);

    i = 2;
    printf("sum: %d\n", i);
    find_series_with_sum(i);

    i = 3;
    printf("sum: %d\n", i);
    find_series_with_sum(i);

    i = 6;
    printf("sum: %d\n", i);
    find_series_with_sum(i);

    i = 7;
    printf("sum: %d\n", i);
    find_series_with_sum(i);

    i = 15;
    printf("sum: %d\n", i);
    find_series_with_sum(i);
}

int main() {
    test_find_series_with_sum();
}

/*
 * output:
 * sum: 1
 * sum: 2
 * sum: 3
 * 1 2
 * sum: 6
 * 1 2 3
 * sum: 7
 * 3 4
 * sum: 15
 * 1 2 3 4 5
 * 4 5 6
 * 7 8
 */
