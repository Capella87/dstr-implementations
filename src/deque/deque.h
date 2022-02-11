#ifndef deque_H
#define deque_H

#include <stdbool.h>
#define OBJ "deque"

typedef int data;

typedef struct node
{
    data d;
    struct node* prev;
    struct node* next;
} node;

typedef struct deque
{
    node* head;
    node* trailer;
    int size;
} deque;

node* get_node(const data d);
bool init_deque(deque* dq);
data front(deque* dq);
data back(deque* dq);
bool push_front(deque* dq, const data d);
bool push_back(deque* dq, const data d);
data pop_front(deque* dq);
data pop_back(deque* dq);

bool traverse(deque* dq);
int get_size(const deque* dq);
bool is_empty(const deque* dq);
bool free_all(deque* dq);

#endif