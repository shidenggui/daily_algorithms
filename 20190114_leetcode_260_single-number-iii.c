/*
 * 关键思路在于如果找到分割字符串的 flag，这里可以利用 
 * xor & (xor - 1) 取得 xor 移除最后一个1后得值，然后同 xor 做 ^
 * xor ^(xor & (xor - 1)) 就可以拿到 xor 最后一个 1 的位置
 */

int split_flag(int *arr, int n) {
    int xor = 0;
    for (int i = 0; i < n; i++)
        xor ^= arr[i];
    
    return xor ^ (xor & (xor - 1));
}

int* singleNumber(int* arr, int n, int* return_size) {
    if (!arr || n <= 1)
        return NULL;
    int flag = split_flag(arr, n);
    
    *return_size = 2;
    // 要 return 的数组必须通过 malloc 分配，不然在函数返回时，对应的内存空间就在 stack 上被销毁了
    int *result = malloc(sizeof(int) * 2);
    for (int i = 0; i < 2; i++)
        result[i] = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] & flag)
            result[0] ^= arr[i];
        else
            result[1] ^= arr[i];
    }
    return result;
}
