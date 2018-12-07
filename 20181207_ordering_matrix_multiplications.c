#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// brute search
int opmat(int *c, int left, int right) {
    if (left == right)
        return 0;
    int min_op = INT_MAX;
    for (int i = left; i < right; i++) {
        int left_op = opmat(c, left, i);
        int right_op = opmat(c, i + 1, right);
        int op = left_op + right_op + c[left - 1] * c[i] * c[right];
        if (op < min_op)
            min_op = op;
    }
    return min_op;
}

int opmatrix(int *c, int n) {
    return opmat(c, 1, n);
}

void test_opmatrix() {
    int c[] = {50, 10, 40 ,30, 5};
    printf("%d", opmatrix(c, 4));
}

int main() {
    test_opmatrix();
}
