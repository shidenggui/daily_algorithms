/*
 * https://leetcode.com/problems/reverse-pairs/submissions/
 * 跟原题有细微的差别，leetcode 上是找出 important reverse pair 
 */
void merge(int *arr, int left, int left_end, int right_end, int *tmp_arr) {
    int right = left_end + 1;
    int left_idx = left;
    int right_idx = right;
    int tmp_idx = left;
    
    while (left_idx <= left_end && right_idx <= right_end) {
        if (arr[left_idx] < arr[right_idx]) {
            tmp_arr[tmp_idx++] = arr[left_idx++];
        }
        else 
            tmp_arr[tmp_idx++] = arr[right_idx++];
    }
    while (left_idx <= left_end) 
        tmp_arr[tmp_idx++] = arr[left_idx++];
    while (right_idx <= right_end)
        tmp_arr[tmp_idx++] = arr[right_idx++];
    
    for (int i = left; i <= right_end; i++) {
        arr[i] = tmp_arr[i];
    }
    return 0;
}

int reverse_pairs(int *arr, int left, int right, int *tmp_arr) {
    if (!arr || right - left <= 0 )
        return 0;
    int mid = left + (right - left) / 2;
    int left_pairs = reverse_pairs(arr, left, mid, tmp_arr);
    int right_pairs = reverse_pairs(arr, mid + 1, right, tmp_arr);

    int pairs = 0;
    for (int i = left, j = mid + 1; i <= mid && j <= right;) {
        if ((long)arr[i] > 2 * (long)arr[j]) {
            pairs += mid - i + 1;
            j++;
        } else 
            i++;
    }
    
    merge(arr, left, mid, right, tmp_arr);
    return left_pairs + right_pairs + pairs;
}

int reversePairs(int* nums, int numsSize) {
    if (!nums || numsSize <= 1)
        return 0;
    int tmp_arr[numsSize];
    return reverse_pairs(nums, 0, numsSize - 1, tmp_arr);
}
