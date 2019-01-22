// 思路：
// 因为是排序数组，所以使用一个头指针，一个尾指针，向中间逼近即可
// 当 sum 较大时，right--, while sum is smaller than target, left++
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
// testcases: [2, 7, 9], 9
int* twoSum(int* arr, int n, int target, int* return_size) {
    if (!arr || n <= 1)
        return NULL;
    int *result = malloc(sizeof(int) * 2);
    *return_size = 2;
    
    int left = 0;
    int right = n - 1;
    int sum;
    while (left < right) {
        sum = arr[left] + arr[right];
        if (sum > target)
            right--;
        else if (sum < target)
            left++;
        else {
            result[0] = left + 1;
            result[1] = right + 1;
            return result;
        }
    }
    return NULL;
}
