int findMin(int* arr, int n) {
    if (!arr || n < 1)
        return 0;
    int left = 0;
    int right = n - 1;
    int mid;
    while (left < right) {
        if (arr[left] < arr[right])
            return arr[left];
        
        mid = left + (right - left) / 2;
        if (arr[mid] > arr[right])
            left = mid + 1;
        else if (arr[mid] < arr[left]) {
            left++;
            right = mid;
        // 跟 153 的区别就是有重复的数字，这是直接退化为 linear search
        } else
            right--;
    }
    return arr[left];
}
