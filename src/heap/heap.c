#include "heap.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Implement Max Heap

inline void swap(Data* a, Data* b)
{
    Data temp = *a;
    *a = *b;
    *b = temp;
}

bool initHeap(Heap* h, const int max)
{
    h->arr = (Data*)malloc(sizeof(Data*) * (max + 1));
    h->count = 0;
    h->max = max;
    return true;
}

bool enqueue(Heap* h, const Data d)
{
    if (h->count == h->max) return false;
    int idx = ++h->count; // 힙 꼬리에 붙는 것으로 가정한다.
    while (idx != 1 && d > h->arr[idx / 2]) // 루트 노드 전까지 혹은 더 큰 값이 위에 있는 경우 전까지 루프
    {
        h->arr[idx] = h->arr[idx / 2]; // 값 이동 -> 공간 확보
        idx = idx / 2;
    }
    h->arr[idx] = d;
    return true;
}

Data dequeue(Heap* h)
{
    if (!h->count) return EOF;
    Data rt = h->arr[1]; // 루트 노드 값 제거
    h->arr[1] = h->arr[h->count--]; // 루트에 힙의 마지막 원소를 갖다 놓는다.

    int idx = 1;
    while (1)
    {
        int childIdx = idx * 2;
        if (childIdx < h->count && h->arr[childIdx] < h->arr[childIdx + 1])
            childIdx++; // 자식 노드 중 오른쪽 자식이 크다면 오른쪽으로 설정
        if (childIdx > h->count || h->arr[idx] >= h->arr[childIdx])
            break;
        swap(&h->arr[childIdx], &h->arr[idx]);
        idx = childIdx;
    }
    return rt;
}

void levelOrder(Heap* h)
{
    for (int i = 1; i <= h->count; i++)
        printf("%d ", h->arr[i]);
    putchar('\n');
}

bool freeAll(Heap* h)
{
    free(h->arr);
    h->count = h->max = 0;
    return true;
}