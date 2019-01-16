/*
 * 发现我之前的实现有 bug，但是 leetcode 也给过了，神奇
 */
int max2(int a, int b) {
    return a > b? a: b;
}

int min2(int a, int b) {
    return a < b? a: b;
}

// arr[i - 1] < k <= arr[i], return i - 1
int binary_search(int *arr, int n, int k) {
    int left = 0;
    int right = n - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (k <= arr[mid]) {
            // 就是这里实现错了，因为可以看到，因为根据 arr[i - 1] < k <= arr[i]
            // 当 i == mid  时，应当返回 i - 1
            // 而 arr[i + 1] >= k > arr[i]，所以下面一个是对的，直接返回 mid 即可
            // if (mid == 0 || k > arr[mid - 1])
            if (mid == 0)  
                return 0
            if (k > arr[mid - 1])
                return mid - 1;
            right = mid - 1;
        } else {
            if (mid == n - 1 || k <= arr[mid + 1])
                return mid;
            left = mid + 1;
        }
    }
    return 0;
}

int length_of_lis(int *arr, int n) {
    if (!arr || n < 1) 
        return 0;

    int lis[n];
    for (int i = 0; i < n; i++)
        lis[i] = 1;

    int max_value[n + 1];
    max_value[0] = INT_MIN;
    max_value[1] = arr[0];
    for (int i = 2; i <= n; i++)
        max_value[i] = INT_MAX;

    int max_len = 1;
    int append_lis;
    for (int i = 1; i < n; i++) {
        lis[i] = 1 + binary_search(max_value, max_len + 1, arr[i]);
        max_len = max2(lis[i], max_len);
        max_value[lis[i]] = min2(arr[i], max_value[lis[i]]);
    }
    return max_len;
}
