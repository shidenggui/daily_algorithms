#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define CARD_SIZE (14)

bool is_continuous(int *arr, int n) {
    if (!arr || n <= 0)
        return false;
    int bucket[CARD_SIZE] = {0};

    for (int i = 0; i < n; i++)
        // 这里是 bucket[arr[i]] 而不是 bucket[i]，测试用例测试的不够仔细
        bucket[arr[i]] += 1;

    int zeros = bucket[0];
    // 这里有个优化的地方，可以直接判断 >= n - 1 
    //即可，因为比如有 4 个 0， 剩下的那个肯定可以组成连续的牌
    // if (zeros == n)
    if (zeros >= n - 1)
        return true;
    int remains = n - zeros;

    int start = 1;
    while (bucket[start] == 0) start++;

    int end = start;
    while (remains > 0) {
        if (bucket[end] == 0)
            end++;
        else if (bucket[end] == 1) {
            remains--;
            end++;
        } else {
            return false;
        }
    }

    if (end - start <= 5)
        return true;
    return false;
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
