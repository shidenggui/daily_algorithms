/*
 * 某个数组中，有两个不同的数只出现了一次，其余数都出现了两次，请找出这两个数。
 * 思路：
 * 对所有数做异或运算，因为相同的两个数进行异或后为 0，所以最后剩下的数一定是那两个只出现一次的数的异或。
 * 而因为这两个数不同，所以他们异或的结果一定不为 0，找出结果中为 1 的那一位 bit idx，这个 idx 满足在其中一位中为 1，另一位中为 0，否则不可能异或结果为 1，根据这个 idx 是否为 1 将数分为 2 组，剩下的就用异或找出只出现一次的数即可。 
 */
#include <stdlib.h>
#include <assert.h>

int find_bit_flag(int *arr, int n) {
    int flag = 1;
    int remain = 0;
    for (int i = 0; i < n; i++)
        remain ^= arr[i];

    // 原来写成 while (remain & flag != flag) flag << 1;
    // 犯了两个错误，首先是 remain & flag 需要加括号，应该为 (remain & flag) != flag
    // 第二是 flag 左移一位后忘记赋值，应该为 flag <<= 1
    // 改正后如下
    while ((remain & flag) != flag) flag <<= 1;
    return flag;
}

void find_number_appear_once(int *arr, int n, int *n1, int *n2) {
    if (!arr || n < 2)
        return;
    int flag = find_bit_flag(arr, n);
    for (int i = 0; i < n; i++) {
        if (flag & arr[i])
            *n1 ^= arr[i];
        else
            *n2 ^= arr[i];
    }
    return;
}

void test_find_number_appear_once() {
    int n1 = 0, n2 = 0;
    find_number_appear_once((int*)&(int[]){2,4,3,6,3,2,5,5}, 8, &n1, &n2);
    assert(n1 == 6);
    assert(n2 == 4);
    
    n1 = 0, n2 = 0;
    find_number_appear_once((int*)&(int[]){2,9,3,7,3,2,5,5}, 8, &n1, &n2);
    assert(n1 == 7);
    assert(n2 == 9);
}

int main() {
    test_find_number_appear_once();
}
