#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// In matrix, every row sorts from small to large, also every column.
// search k in matrix, if exist, return x,y coordinates.
bool search(int *matrix, int m, int n, int k, int *x, int *y) {
    if (matrix == NULL)
        return false;
    if (m <= 0 || n <= 0)
        return false;
    int tmp;
    for (int i = 0, j = n - 1; i < m && j >= 0;) {
        tmp = matrix[i * n + j];
        if (k < tmp)
            j--;
        else if (k > tmp)
            i++;
        else {
            *x = i;
            *y = j;
            return true;
        }
    }
    return false;
}

void test_search() {
    int matrix[4][4] = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15},
    };
    int x, y;
    assert(search((int *)matrix, 4, 4, 7, &x, &y) == true);
    assert(x == 2);
    assert(y == 1);
    printf("find %d in matrix, x: %d, y: %d\n", 7, x, y);


    assert(search((int *)matrix, 4, 4, 0, &x, &y) == false);

    assert(search(NULL, 4, 4, 0, &x, &y) == false);
    assert(search((int *)matrix, 0, 4, 0, &x, &y) == false);
}

int main() {
    test_search();
}
