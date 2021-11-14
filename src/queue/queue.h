#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#define OBJ "queue"

typedef int Data;

typedef struct _node
{
    Data d;
    struct _node* prev;
    struct _node* next;
} Node;

typedef struct _queue
{
    Node* head;
    Node* trailer;
    int size;
} Queue;

Node* get_node(const Data d);
bool init_queue(Queue* q);
bool enqueue(Queue* q, const Data d);
Data front(Queue* q);
Data back(Queue* q);
Data dequeue(Queue* q);

bool traverse(Queue* q);
int get_size(const Queue* q);
bool is_empty(const Queue* q);
bool free_all(Queue* q);

#endif