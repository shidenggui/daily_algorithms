#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void fatal_error(char *msg) {
    printf("fatal error: %s\n", msg);
    exit(1);
}

typedef struct DisjointSetStruct {
    int size;
    int *arr;
} DisjointSetStruct, *DisjointSet;

DisjointSet create_disjoint_set(int size) {
    DisjointSet s = malloc(sizeof(DisjointSetStruct));
    if (s == NULL)
        fatal_error("out of space");
    s->arr = malloc(sizeof(int) * size);
    if (s->arr == NULL)
        fatal_error("out of space");
    for (int i = 0; i < size; i++)
        s->arr[i] = -1;
    s->size = size;
    return s; 
}

void free_disjoint_set(DisjointSet s) {
    if (s == NULL)
        return;
    free(s->arr);
    free(s);
}

int find(int s1, DisjointSet s) {
    // if(s->arr[s1] == -1)
    // not equal -1, because when union, root value become more small by rank change
    if (s->arr[s1] < 0)
        return s1;
    return s->arr[s1] = find(s->arr[s1], s);
}

// union by rank
void set_union(int s1, int s2, DisjointSet s) {
    s1 = find(s1, s);
    s2 = find(s2, s);
    if (s1 == s2)
        return;
    if (s->arr[s1] < s->arr[s2]) {
        s->arr[s2] = s1;
        return;
    }
    if (s->arr[s1] == s->arr[s2])
        s->arr[s2]--;
    s->arr[s1] = s2;
}

void test_disjoint_set() {
    DisjointSet s = create_disjoint_set(10);
    assert(find(5, s) != find(6, s));
    set_union(5, 6, s);
    assert(find(5, s) == find(6, s));

    assert(find(6, s) != find(8, s));
    set_union(7, 8, s);
    set_union(5, 7, s);
    assert(find(6, s) == find(8, s));
    free_disjoint_set(s);
}

int main() {
    test_disjoint_set();
}
