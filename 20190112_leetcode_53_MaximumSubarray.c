/*
 * 算法的魅力。我看书的开篇算法。不过我在写 dp 函数的时候第一次也失误了。果然，不复习的话一切就像流水般逝去。不过“雪儿实习，不亦说乎”
 * f_max(n) = max{f_max(n - 1) + arr[i], arr[i]}
 */
int maxSubArray(int* arr, int n) {
    int max_sum = arr[0];
    int sum = arr[0];
    for (int i = 1; i < n; i++) {
        sum += arr[i];
        if (arr[i] > sum)
            sum = arr[i];
            
        if (sum > max_sum)
            max_sum = sum;
    }
    return max_sum;
}
