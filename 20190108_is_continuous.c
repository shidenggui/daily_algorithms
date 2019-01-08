#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define CARD_SIZE (14)
bool is_continuous(int *arr, int n) {
    if (!arr || n <= 0)
        return false;

    int bucket[CARD_SIZE] = {0};
    for (int i = 0; i < n; i++)
        bucket[arr[i]] += 1;

    int zeros = bucket[0];
    if (zeros >= n - 1)
        return true;

    int start = 1;
    // 这里是在 bucket 找到第一张不为 0 的牌
    // while (arr[start] == 0) start++;
    while (bucket[start] == 0) start++;
    int end = start;

    int remain = n - zeros;
    while (remain > 0) {
        if (bucket[end] == 0)
            end++;
        else if (bucket[end] > 1)
            return false;
        else {
            end++;
            remain--;
        }
    }
    // end 此时指向的是最后一张牌的后面，所以需要 end--;
    end--;
    return end - start + 1 <= 5;
} 

void test_is_continuous() {
    assert(is_continuous((int*)&(int[]){0, 0, 0, 0, 0}, 5) == true);
    assert(is_continuous((int*)&(int[]){0, 0, 1, 0, 0}, 5) == true);
    assert(is_continuous((int*)&(int[]){0, 1, 1, 0, 0}, 5) == false);
    assert(is_continuous((int*)&(int[]){0, 1, 0, 0, 10}, 5) == false);
    assert(is_continuous((int*)&(int[]){0, 1, 3, 4, 5}, 5) == true);
    assert(is_continuous((int*)&(int[]){0, 1, 3, 3, 5}, 5) == false);
    assert(is_continuous((int*)&(int[]){0, 0, 3, 3, 5}, 5) == false);
    assert(is_continuous((int*)&(int[]){0, 0, 3, 7, 5}, 5) == true);
    assert(is_continuous((int*)&(int[]){0, 0, 3, 8, 5}, 5) == false);
}

int main() {
    test_is_continuous();
}
