int searchInsert(int* arr, int n, int k) {
    if (!arr || n < 1)
        return -1;
    int left = 0;
    int right = n - 1;
    int mid;
    // 最后一轮迭代肯定是 left = right
    // 此时 mid = left
    // 如果 k < arr[left], right = left - 1，此时 k 插入的 idx 为 left
    // 如果 k > arr[left]，则 left = mid + 1 = left + 1，即 arr[left] > k，此时 k 插入的 idx 为 left
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (k < arr[mid])
            right = mid - 1;
        else if (k > arr[mid])
            left = mid + 1;
        else
            return mid;
    }
    return left;
}
