// Stack ADT implementation ... COMP9024 17s2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct node {
    int data;
    struct node *next;
} NodeT;

typedef struct StackRep {
    int    height;
    NodeT *top;
} StackRep;

// set up empty stack
stack newStack() {
    stack S = malloc(sizeof(StackRep));
    S->height = 0;
    S->top = NULL;
    return S;
}

// remove unwanted stack
void dropStack(stack S) {
    NodeT *curr = S->top;
    while (curr != NULL) {
        NodeT *temp = curr->next;
        free(curr);
        curr = temp;
    }
    free(S);
}

// check whether stack is empty
int StackIsEmpty(stack S) {
    return (S->height == 0);
}

// insert an int on top of stack
void StackPush(stack S, int v) {
    NodeT *new = malloc(sizeof(NodeT));
    assert(new != NULL);
    new->data = v;
    new->next = S->top;
    S->top = new;
    S->height++;
}

// remove int from top of stack
int StackPop(stack S) {
    assert(S->height > 0);
    NodeT *head = S->top;
    S->top = S->top->next;
    S->height--;
    int d = head->data;
    free(head);
    return d;
}

// Additional functions.

// prints the contents of stack in string form.
void StackPrint(stack S, char **words) {
    if (!(StackIsEmpty(S))) {
        stack temp;
        int v;
        temp = newStack();
        v = StackPop(S);
        StackPush(temp, v);
        printf("%s", words[v]);
        while (!(StackIsEmpty(S))) {
            v = StackPop(S);
            StackPush(temp, v);
            printf(" -> %s", words[v]);
        }
        printf("\n");
        while (!(StackIsEmpty(temp))) {
            v = StackPop(temp);
            StackPush(S, v);
        }
        dropStack(temp);
    }
}

// return ths top integer of a stack.
int topStack(stack S) {
    assert(S->height > 0);
    return S->top->data;
}

// return the height of a stack.
int heightStack(stack S) {
    return S->height;
}
