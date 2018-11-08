#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

void fatal_error(char *msg) {
    printf("fatal_error: %s\n", msg);
    exit(1);
}

void error(char *msg) {
    printf("error: %s\n", msg);
    exit(1);
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

typedef struct HeapStruct {
    int capacity;
    int size;
    int *arr;
} HeapStruct, *Heap;

Heap create_heap(int size) {
    Heap h = malloc(sizeof(HeapStruct));
    if (h == NULL)
        fatal_error("out of space");

    // one more space for sentinel
    h->arr = malloc(sizeof(int) * (size + 1));
    if (h->arr == NULL)
        fatal_error("out of space");

    h->arr[0] = INT_MIN;
    h->capacity = size;
    h->size = 0;
    return h;
}

void free_heap(Heap h) {
    if (h == NULL)
        return;

    free(h->arr);
    free(h);
}

bool is_empty(Heap h) {
    return h->size == 0;
}

bool is_full(Heap h) {
    return h->size == h->capacity;
}

void insert(int value, Heap h) {
    if (is_full(h))
        error("Heap is full, cant insert");

    int i;
    for (i=++h->size; h->arr[i / 2] > value; i /= 2)
        h->arr[i] = h->arr[i / 2];
    h->arr[i] = value;
}

void percolate_down(int *arr, int i, int size) {
    int child;
    int tmp = arr[i];
    while (2 * i <= size) {
        child = 2 * i;
        if (child != size && arr[child + 1] < arr[child])
            child++;

        if (arr[child] > tmp)
            break;

        arr[i] = arr[child];
        i = child;
    }
    arr[i] = tmp;
}

int delete_min(Heap h) {
    if (is_empty(h))
        error("Heap is empty, cant delete min");

    // delete min
    swap(&h->arr[1], &h->arr[h->size]);
    h->size--;

    // balance
    percolate_down(h->arr, 1, h->size);
    return h->arr[h->size + 1];
}

int main() {

}
