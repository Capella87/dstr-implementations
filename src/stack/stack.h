#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef int Data;
typedef struct _node
{
    Data d;
    struct _node* next;
    struct _node* prev;
} Node;

typedef struct _stack
{
    struct _node* head;
    struct _node* trailer;
    int size;
} Stack;

Node* get_node(const Data d);
bool init_stack(Stack* stk);
bool push(Stack* stk, const Data d);
Data pop(Stack* stk);
Data peek(const Stack* stk);

bool traverse(Stack* stk);
int get_size(const Stack* stk);
bool is_empty(const Stack* stk);
bool free_all(Stack* stk);

#endif