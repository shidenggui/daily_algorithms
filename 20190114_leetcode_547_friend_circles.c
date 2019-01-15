/*
 * 朋友圈，由两种解法，union set 或者 dfs
 * 简直一箭双雕，一道题复习两种思路
 */

// 首先是用 union set，将所有的朋友关系都进行 union，最后 arr 里面的 set 数量可以通过 arr[i] < 0 来统计
// 时间复杂度 O(N^2 * LogN)
// 8 ms beat 50%
int find(int set, int *arr) {
    if (arr[set] < 0)
        return set;
    return arr[set] = find(arr[set], arr);
}

void union_set(int set1, int set2, int *arr) {
    set1 = find(set1, arr);
    set2 = find(set2, arr);
    if (set1 == set2)
        return;
    if (arr[set1] < arr[set2]) {
        arr[set2] = set1;
    } else {
        if (arr[set1] == arr[set2])
            arr[set2]--;
        arr[set1] = set2;
    }
}

int findCircleNum(int** M, int row, int col) {
    if (!M || row < 1 || col < 1)
        return 0;
    
    int arr[row];
    memset(arr, -1, sizeof(arr));
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            if (i != j && M[i][j])
                union_set(i, j, arr);
    }
    
    int circle = 0;
    for (int i = 0; i < row; i++) {
        if (arr[i] < 0)
            circle++;
    }
    return circle;
    
    
}

// dfs, 4ms beat 100
// 时间复杂度 O(N^2)

void visit(int i, int **M, int n, bool *visited) {
    visited[i] = true;
    for (int j = 0; j < n; j++) {
        if (i != j && !visited[j] && M[i][j])
            visit(j, M, n, visited);
    }
}

int findCircleNum(int** M, int row, int col) {
    if (!M || row < 1 || col < 1)
        return 0;
    bool visited[row];
    for (int i = 0; i < row; i++)
        visited[i] = false;

    int count = 0;
    for (int i = 0; i < row; i++) {
        if (!visited[i]) {
            visit(i, M, row, visited);
            count++;
        }
    }
    return count;
}
