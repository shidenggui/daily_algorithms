#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

bool find_number_with_sum(int *arr, int n, int k, int *n1, int *n2) {
    if (!arr || n < 2)
        return false;
    int start = 0;
    int end = n - 1;
    while (start < end) {
        int sum = arr[start] + arr[end];
        if (sum < k)
            start++;
        else if (sum > k)
            end--;
        else {
            *n1 = arr[start];
            *n2 = arr[end];
            return true;
        }
    }
    return false;
}

void test_find_number_with_sum() {
    int n1 = 0, n2 = 0;
    assert(find_number_with_sum((int*)&(int[]){0, 1}, 2, 1, &n1, &n2) == true);
    assert(n1 == 0 && n2 == 1);

    n1 = 0;
    n2 = 0;
    assert(find_number_with_sum((int*)&(int[]){0, 1, 2}, 3, 3, &n1, &n2) == true);
    assert(n1 == 1 && n2 == 2);

    n1 = 0;
    n2 = 0;
    assert(find_number_with_sum((int*)&(int[]){0, 1, 2}, 3, 4, &n1, &n2) == false);

    n1 = 0;
    n2 = 0;
    assert(find_number_with_sum((int*)&(int[]){1, 2, 4, 7, 11, 15}, 6, 15, &n1, &n2) == true);
    assert(n1 == 4 && n2 == 11);

    n1 = 0;
    n2 = 0;
    assert(find_number_with_sum((int*)&(int[]){1, 2, 4, 7, 11, 15}, 6, 18, &n1, &n2) == true);
    assert(n1 == 7 && n2 == 11);
}

int main() {
    test_find_number_with_sum();
}
