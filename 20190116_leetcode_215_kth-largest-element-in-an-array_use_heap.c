/*
 * 这个题用 heap 的话 4ms ，beat 90%
 * 不过这里没有用到 heap insert 的逻辑
 */
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void percolate_down(int i, int *arr, int n) {
    int value = arr[i];
    int child;
    while (2 * i + 1 <= n - 1) {
        child = 2 * i + 1;
        if (child + 1 <= n - 1 && arr[child + 1] > arr[child])
            child++;
        
        if (value >= arr[child])
            break;
        arr[i] = arr[child];
        i = child;
    }
    arr[i] = value;
}

int dequeue(int *arr, int n) {
    int max_value = arr[0];
    swap(&arr[0], &arr[n - 1]);
    percolate_down(0, arr, n - 1);
    return max_value;
}


void build_heap(int *arr, int n) {
    for (int i = n / 2; i >= 0; i--)
        percolate_down(i, arr, n);
}

int g_invalid = false;

int findKthLargest(int* arr, int n, int k) {
    if (!arr || n < 1 || k < 1) {
        g_invalid = true;
        return 0;
        
    }
    build_heap(arr, n);
    int target;
    for (int i = 0; i < k; i++)
        target = dequeue(arr, n--);
    return target;
    
}
