/*
 * 给出两个数组，分别为入栈队列和出栈队列，判断出栈队列是否可能由对应的入栈队列构成
 * 用一个栈模拟对应的出入栈，如果模拟失败则不是。
 * 关键点：
 * 从出栈队列开始检查，当对应的出栈元素对应的栈为空或者不在栈顶是，从对应的入栈队列开始压入元素直到找到对应的出栈元素为止，如果遍历了所有入栈数组还是没找到，则直接返回 false。
 * 找到后入栈元素 + 1 跳过该需要出栈的元素。
 * 如果栈顶为对应的出栈元素，则直接弹出。
 */
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define ETOS (-1)

void fatal_error(char *msg) {
    printf("fatal error:%s\n", msg);
    exit(1);
}

void error(char *msg) {
    printf("error:%s\n", msg);
    exit(1);
}

typedef struct StackRecord {
    int *arr;
    int capacity;
    int top;
} StackRecord, *Stack;

Stack create_stack(unsigned size) {
   Stack s = malloc(sizeof(StackRecord)) ;
   if (s == NULL)
       fatal_error("out of space");

   s->arr = malloc(sizeof(int) * size);
   if (s->arr == NULL)
       fatal_error("out of space");

   s->capacity = size;
   s->top = ETOS;
   return s;
}

void free_stack(Stack s) {
    if (s == NULL)
        return;
    free(s->arr);
    free(s);
}

bool is_empty(Stack s) {
    return s->top == ETOS;
}

bool is_full(Stack s) {
    return s->top == s->capacity - 1;
}

void push(int value, Stack s) {
    if (is_full(s)) {
        error("stack is full, cant push");
    }

    s->top++;
    s->arr[s->top] = value;
}

void pop(Stack s) {
    if (is_empty(s)) {
        error("stack is empty, cant pop");
    }
    s->top--;
}

int top(Stack s) {
    if (is_empty(s)) {
        error("stack is empty, cant top");
    }
    return s->arr[s->top];
}


bool is_proper_order(int *push_stack, int *pop_stack, int n) {
    if (push_stack == NULL || pop_stack == NULL  || n <= 0)
        return false;

    Stack s = create_stack(n);
    int i = 0;
    int j = 0;
    for (;i < n; i++) {
        // 入栈为空或者栈顶元素不为出栈序列中对应的元素，将入栈序列的元素入栈直到遇到对应的出栈元素为止，如果全部入栈了还没遇到，返回 false
        if (is_empty(s) || top(s) != pop_stack[i]) {
            while (j < n && push_stack[j] != pop_stack[i]) {
                push(push_stack[j], s);
                j++;
            }
            if (j == n)
                return false;
            // 如果在入栈队列中找到了对应的压栈元素，则++跳过该元素
            j++;
        // 如果栈顶元素为出栈元素，弹出
        } else {
            pop(s);
        }
    }
    free_stack(s);
    return true;
}


void test_is_proper_order() {
    assert(is_proper_order((int[]){1}, (int[]){1}, 1));
    assert(is_proper_order((int[]){1, 2}, (int[]){1, 2}, 2));

    assert(is_proper_order((int[]){1, 2}, (int[]){2, 1}, 2));
    assert(is_proper_order((int[]){1, 2}, (int[]){3, 1}, 2) == false);

    assert(is_proper_order((int[]){1, 2, 3, 4, 5}, (int[]){5, 4, 3, 2, 1}, 5) == true);
    assert(is_proper_order((int[]){1, 2, 3, 4, 5}, (int[]){4, 3, 5, 2, 1}, 5) == true);
    assert(is_proper_order((int[]){1, 2, 3, 4, 5}, (int[]){4, 3, 5, 1, 2}, 5) == false);
}

int main() {
    test_is_proper_order();
}
