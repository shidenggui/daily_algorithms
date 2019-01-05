/*
 * leetcode: https://leetcode.com/problems/consecutive-numbers-sum/submissions/
 * 有种比剑指 offer 好 N 倍的解法，见 https://zhanghuimeng.github.io/post/leetcode-829-consecutive-numbers-sum/ 
 * 时间复杂度 O(Sqrt(N))
 * 我一开始也想到了等差数列求和公式，但是当时为了更快的刷题，直接接纳了《剑指 offer》上的解法，这样虽然很快掌握了一种解法，
 * 但有时候未免一叶障目
 */
#include <stdio.h>

void print_sequence(int small, int big) {
    while (small <= big) {
        printf("%d ", small++);
    }
    printf("\n");
}
void find_continuous_sequence_with_sum2(int n) {
    int small = 1;
    int big = 2;
    int max_big = n / 2 + 1;
    int sum = small + big;
    // 更傻的是这里还忘记了判断 small < big，这种解法太容易出错了，还是见下面利用等差数列求和公式的解法更好
    // while (big <= max_big) {
    while (big <= max_big && small < big) {
        if (sum < n) {
            sum += ++big;
        } else if (sum > n) {
            // 这里错了，不管是 small 还是 bug 都是递增的
            //sum -= small--;
            sum -= small++;
        } else {
            print_sequence(small, big);
            sum += ++big;
        }
    }
}

void find_continuous_sequence_with_sum(int n) {
    for (int i = 2; ; i++) {
        int ix = n - i * (i - 1) / 2;
        if (ix <= 0)
            break;
        if (ix % i == 0) {
            print_sequence(ix / i, ix / i + i - 1);
        }
    }
}


void test_find_continuous_sequence_with_sum() {
    int i;

    i = 1;
    printf("sum: %d\n", i);
    find_continuous_sequence_with_sum(i);

    i = 2;
    printf("sum: %d\n", i);
    find_continuous_sequence_with_sum(i);

    i = 3;
    printf("sum: %d\n", i);
    find_continuous_sequence_with_sum(i);

    i = 6;
    printf("sum: %d\n", i);
    find_continuous_sequence_with_sum(i);

    i = 7;
    printf("sum: %d\n", i);
    find_continuous_sequence_with_sum(i);

    i = 9;
    printf("sum: %d\n", i);
    find_continuous_sequence_with_sum(i);

    i = 15;
    printf("sum: %d\n", i);
    find_continuous_sequence_with_sum(i);
}

int main() {
    test_find_continuous_sequence_with_sum();
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
