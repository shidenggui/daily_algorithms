/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

// first: arr[mid] == k && arr[mid - 1] != k
// last: arr[mid] == k && arr[mid + 1] != k
int binary_search(int *arr, int n, int k, bool find_first) {
    int left = 0;
    int right = n - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (k < arr[mid])
            right = mid - 1;
        else if (k > arr[mid])
            left = mid + 1;
        else {
            if (find_first) {
                if (mid == 0 || arr[mid - 1] != k)
                    return mid;
                right = mid - 1;
            } else {
                if (mid == n - 1 || arr[mid + 1] != k)
                    return mid;
                left = mid + 1;
            }
        }
    }
    return -1;
}

int find_first(int *arr, int n, int k) {
    return binary_search(arr, n, k, true);
}

int find_last(int *arr, int n, int k) {
    return binary_search(arr, n, k, false);
}

int* searchRange(int* arr, int n, int target, int* return_size) {
    *return_size = 2;
    int *result = malloc(sizeof(int) * 2);
    result[0] = result[1] = -1;
    
    int first = find_first(arr, n, target);
    if (first == -1)
        return result;
    
    int last = find_last(arr + first, n - first, target) + first;
    
    result[0] = first;
    result[1] = last;
    return result;
}
