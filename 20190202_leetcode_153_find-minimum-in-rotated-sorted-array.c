int findMin(int* arr, int n) {
    if (!arr || n < 1)
        return 0;
    
    int left = 0;
    int right = n - 1;
    int mid;
    // left < right 不能等于，等于的话会出现无限循环，这是跟二分查找不同的地方
    while (left < right) {
        if (arr[left] < arr[right])
            return arr[left];
        
        mid = left + (right - left) / 2;
        // arr[mid] 本身肯定不可能是最小值，所以 left = mid + 1
        if (arr[mid] > arr[right]) 
            left = mid + 1;
        // arr[left] 肯定不可能是最小值，所以 left++，而 arr[mid] 可能是，所以 right = mid
        else if (arr[mid] < arr[left]) {
            left++;
            right = mid;
        }
    }
    return arr[left];
}
