#include <stdio.h>

void print_sequence(int small, int big) {
    while (small <= big) {
        printf("%d ", small++);
    }
    printf("\n");
}
void find_continuous_sequence_with_sum(int n) {
    int small = 1;
    int big = 2;
    int max_big = n / 2 + 1;
    int sum = small + big;
    while (big <= max_big) {
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
