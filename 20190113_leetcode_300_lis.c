/*
 * https://leetcode.com/problems/longest-increasing-subsequence/submissions/
 * 找到给出数组中，最长的递增序列，这是一个 dp 问题。
 * 方程如下: LIS[n] = max(1, LIS[i] + 1 (0 <= i < n))
 * 然后返回 max(LIS) 即可
 */
int max2(int a, int b) {
    return a > b? a: b;
}
int lengthOfLIS(int* arr, int n) {
    if (!arr || n < 2)
        return n;
    
    int max_len = 1;
    
    int lis[n];
    for (int i = 0; i < n; i++)
        lis[i] = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i])  {
                lis[i] = max2(lis[j] + 1, lis[i]);
            }
        }
        // 最后更新 max_len 就可以了，不必每次更新
        max_len = max2(lis[i], max_len);
    }
    
    return max_len;
}

// 下面这个版本 leetcode 可以 100% 了，不过整体还是 O(N^2) 的复杂度
// 如果要 NLogN 的话，将查找 
// if (arr[i] > max_value[j]) {
//     lis[i] = j + 1;
//     break;
// }
//
// 这一部分改为二分查找即可
int lengthOfLIS(int* arr, int n) {
    if (!arr || n < 2)
        return n;

    int max_len = 1;

    int lis[n];
    for (int i = 0; i < n; i++)
        lis[i] = 1;

    int max_valud[n];
    max_value[1] = arr[1];
    for (int i = 2; i < n; i++)
        max_value[i] = INT_MAX;

    for (int i = 0; i < n; i++) {
        for (int j = max_len; j > 0; j--) {
            if (arr[i] > max_value[j]) {
                lis[i] = j + 1;
                break;
            }
        }
        max_len = max2(lis[i], max_len);
        max_value[lis[i]] = min2(arr[i], max_value[lis[i]]);
    }

    return max_len;
}

