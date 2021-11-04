#ifndef HEAP_H
#define HEAP_H
#include <stdbool.h>

typedef int Data;
typedef struct _heap
{
    Data* arr;
    int count;
    int max;
} Heap;

inline void swap(Data* a, Data* b);

bool init_heap(Heap* h, const int max);
bool enqueue(Heap* h, const Data d);
Data dequeue(Heap* h);
void level_order(Heap* h);
bool free_all(Heap* h);

bool enqueue_min(Heap* h, const Data d);
Data dequeue_max(Heap* h);

#endif