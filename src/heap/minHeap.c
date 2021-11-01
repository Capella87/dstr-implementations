#include "heap.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Implement Min Heap

bool enqueue_min(Heap* h, const Data d)
{
    if (h->count == h->max) return false;
    int idx = ++h->count;
    while (idx != 1 && d < h->arr[idx / 2])
    {
        h->arr[idx] = h->arr[idx / 2];
        idx /= 2;
    }
    h->arr[idx] = d;
    return true;
}

Data dequeue_max(Heap* h)
{
    if (!h->count) return EOF;
    Data rt = h->arr[1];
    h->arr[1] = h->arr[h->count--];

    int idx = 1;
    while (1)
    {
        int childIdx = idx * 2;
        if (childIdx < h->count && h->arr[childIdx] > h->arr[childIdx + 1])
            childIdx++;
        if (childIdx > h->count || h->arr[idx] >= h->arr[childIdx])
            break;
        swap(&h->arr[idx], &h->arr[childIdx]);
        idx = childIdx;
    }
    return rt;
}