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

bool initHeap(Heap* h, const int max);
bool enqueue(Heap* h, const Data d);
Data dequeue(Heap* h);
void levelOrder(Heap* h);
bool freeAll(Heap* h);

#endif