/*
 * 用了更加友好的命名，
 * dfs 确实简洁而且更快
 * 4ms beat 100%
 */
void visit(int self, int **M, int n, bool *visited) {
    visited[self] = true;
    for (int friend = 0; friend < n; friend++) {
        if (friend != self && !visited[friend] && M[self][friend])
            visit(friend, M, n, visited);
    }
}

int findCircleNum(int** M, int n, int MColSize) {
    if (!M || n < 1)
        return 0;
    bool visited[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visit(i, M, n, visited);
            count++;
        }
    }
    return count;
    
}
