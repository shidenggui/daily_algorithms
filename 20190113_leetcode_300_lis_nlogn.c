/*
 * lis 的 nlogn 解法，这个 binary search 有点绕，感觉我想复杂了，不知道有没有简洁的版本
 * 这里的关键在于搜索时要满足 arr[i - 1] < k <= arr[i]
 * 这样的话如果 k > arr[mid]，只需要满足 mid != n - 1 || arr[mid + 1] >= k 即可返回
 * 而 k <= arr[mid] 时只需要满足 mid == 0 || arr[mid - 1] < k 即可
 * 这样一想感觉是我想复杂了
 *
 * 这里的二分查找跟找第一个出现的 k 和最后出现的 k 有点像，不过那个实在 arr[mid] == k 时做对应的判断，而我们这里可能根本就没有对应的 k 值存在
 *
 */

int binary_search(int *arr, int n, int k) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (k > arr[mid]){
            if (mid == n - 1 || k <= arr[mid + 1] )
                return mid;
            left = mid + 1;
        } else {
            if (mid == 0 || arr[mid - 1] < k)
                return mid;
            right = mid - 1;
        }
    }
    return 0;
}

int max2(int a, int b) {
    return a > b? a: b;
}

int min2(int a, int b) {
    return a < b? a: b;
}

int lengthOfLIS(int* arr, int n) {
    if (!arr || n < 1)
        return 0;
    int lis[n];
    for (int i = 0; i < n; i++)
        lis[i] = 1;
    
    int max_value[n + 1];
    max_value[0] = INT_MIN;
    max_value[1] = arr[0];
    for (int i = 2; i < n + 1; i++) 
        max_value[i] = INT_MAX;
    
    int max_len = 1;
    
    for (int i = 1; i < n; i++) {
        lis[i] =  binary_search(max_value, max_len + 1, arr[i]) + 1;
        max_len = max2(lis[i], max_len);
        max_value[lis[i]] = min2(max_value[lis[i]], arr[i]);
    }
    return max_len;
}/
