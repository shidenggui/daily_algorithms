/*
 * 今天做的时候突然发现一个优化，可以把查询数量减少一半
 * 因为 M 里面 n * n 的矩阵是对称的，所以
 * 第二次循环只需要 j < i 就可以了，这样的话，也不需要判断 i != j 了，不过结果还是 5ms 就是了
 */
int find(int set, int *arr) {
    if (arr[set] < 0)
        return set;
    return arr[set] = find(arr[set], arr);
} 

void union_set(int s1, int s2, int *arr) {
    s1 = find(s1, arr);
    s2 = find(s2, arr);
    if (s1 == s2)
        return;
    
    if (arr[s1] < arr[s2])
        arr[s2] = s1;
    else {
        if (arr[s1] == arr[s2])
            arr[s2]--;
        arr[s1] = s2;
    }
}

int findCircleNum(int** M, int n, int col) {
    if (!M || n < 1)
        return 0;
    int arr[n];
    memset(arr, -1, sizeof(arr));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (M[i][j])
                union_set(i, j, arr);
        }
    }
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0)
            count++;
    }
    return count;
}
