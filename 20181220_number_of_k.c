/*
 * 求 0 到一个正整数 n 的过程中，数字 k(0 到 9) 出现了几次
 * ## 1. 暴力搜索
 * 直接对从 0 到 n 的数，每个数通过 % 10 并 /10 来求出对应的 k 的数量，然后累加
 * 时间复杂度为 O(N*Log_10^N)
 * ## 2. 利用规律，只需要 O(Log_10^N)
 * 如果从右往左扫，令当前扫描到的数字为 current, 
 * current 左边的数字称为 prev，右边的数字称为 former，当前的位数称为 base，比如个位就是 1，十位就是 10。
 * 则在 current 这一位上，k 出现的次数有两部份决定
 * 1. 通过 prev 可以知道 k 在该位出现了多少次，比如 25, k 为 1，则在个位 5 的时候，prev 为 2，此时我们知道 1 在个位出现了至少两次，因为 prev 为 0，1 的时候，个位都可以出现对应的 1，这一部分的数量为 prev * base
 * 2. 根据 current 决定，如果 current 为 k 的话，则 former 决定了 current 上的 k 出现了多少次，即为。比如 11，当在十位的 1 时，former 为 1，10~11 十位出现了 2次。则根据 current 出现的次数为 1。如果 current > k 的话，则为 base，考虑 21，当在十位的 2 时，2 > 当前的 k 值 1，所以其中出现了10~19 ，即为此时的 base shl，总结如下
 * count = prev * base + former_count
 * former_count 分为以下三种情况
 * 1. current < k 为 0
 * 2. current == k 为 former + 1
 * 3. current > k 为 base
 * 假设当前数为 remain, 当前扫描的数为 current，
 * 则 prev = remain / 10
 * former = n % base
 * 具体代码如下
 * */
#include <assert.h>

int number_of_k_brute(int n, int k) {
    int count = 0;
    for (int i = 0; i <= n; i++) {
        int num = i;
        while (num > 0) {
            if (num % 10 == k)
                count++;
            num /= 10;
        }
    }
    return count;
}

int number_of_k(int n, int k) {
    int remain = n;
    int base = 1;
    int count = 0;
    while (remain > 0) {
        int current = remain % 10;
        remain /= 10;

        count += remain * base;
        if (current > k)
            count += base;
        else if (current == k)
            count += n % base + 1;

        base *= 10;
    }
    return count;
}

void test_number_of_k() {
    assert(number_of_k_brute(0, 1) == 0);
    assert(number_of_k_brute(1, 1) == 1);
    assert(number_of_k_brute(2, 1) == 1);
    assert(number_of_k_brute(10, 1) == 2);
    assert(number_of_k_brute(11, 1) == 4);
    assert(number_of_k_brute(19, 1) == 12);
    assert(number_of_k_brute(100, 1) == 21);
    printf("101:%d\n", number_of_k_brute(101, 1));
    printf("110:%d\n", number_of_k_brute(110, 1));
    printf("111:%d\n", number_of_k_brute(111, 1));
    printf("201:%d\n", number_of_k_brute(201, 1));
    printf("1000:%d\n", number_of_k_brute(1000, 1));
    printf("1000:%d\n", number_of_k_brute(1000, 6));

    assert(number_of_k(0, 1) == 0);
    assert(number_of_k(1, 1) == 1);
    assert(number_of_k(2, 1) == 1);
    assert(number_of_k(10, 1) == 2);
    assert(number_of_k(11, 1) == 4);
    assert(number_of_k(19, 1) == 12);
    assert(number_of_k(100, 1) == 21);
    printf("101:%d\n", number_of_k(101, 1));
    printf("110:%d\n", number_of_k(110, 1));
    printf("111:%d\n", number_of_k(111, 1));
    printf("201:%d\n", number_of_k(201, 1));
    printf("534:%d\n", number_of_k(534, 1));
    printf("530:%d\n", number_of_k(530, 1));
    printf("504:%d\n", number_of_k(504, 1));

    printf("514:%d\n", number_of_k(514, 1));
    printf("1000:%d\n", number_of_k(1000, 1));
    printf("1000:%d\n", number_of_k(1000, 6));
}

int main () {
    test_number_of_k();
}
