#include <stdio.h>
#include <stdlib.h>

typedef struct heap
{
    int* data;
    int index;
    int max_capacity;
} heap;

// Swap two numbers
inline void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Initialize a heap
heap* init_heap(int max_capacity)
{
    heap* rt = (heap*)malloc(sizeof(heap));

    // This heap does not use the first index of array
    rt->data = (int*)malloc(sizeof(int) * (max_capacity + 1));

    rt->index = 0;
    rt->max_capacity = max_capacity;

    return rt;
}

// Up_heap or down_heap
void heapify(heap* h, int idx, void (*direction)(heap*, int))
{
    direction(h, idx);
}

// Move a node up until reaching a proper place from the bottom
void up_heap(heap* h, int idx)
{
    int parent = idx / 2;

    if (parent > 0 && h->data[parent] > h->data[idx])
    {
        swap(&h->data[parent], &h->data[idx]);
        up_heap(h, parent);
    }
}

// Move a node down until reaching a proper place from the top
void down_heap(heap* h, int idx)
{
    int target = idx;
    int child = idx * 2;

    if (child <= h->index && h->data[idx] > h->data[child])
        target = child++;
    if (child <= h->index && h->data[target] > h->data[child])
        target = child;

    if (target != idx)
    {
        swap(&h->data[idx], &h->data[target]);
        down_heap(h, target);
    }
}

// Insert an element to the heap
void insert(heap* h, int data)
{
    if (h->index == h->max_capacity) return;

    h->data[++(h->index)] = data;
    heapify(h, h->index, up_heap);
}

// Get the min value from the heap
int get_min(heap* h)
{
    if (!h->index)
    {
        printf("No element in the heap\n");
        return -1;
    }

    int rt = h->data[1];
    h->data[1] = h->data[h->index--];
    heapify(h, 1, down_heap);

    return rt;
}

// Deallocate all resources of heap
void free_heap(heap* h)
{
    free(h->data);
    free(h);
}

// Print all elements of heap
// Heap does not always follow sorted order.
void print_heap(heap* h)
{
    for (int i = 1; i <= h->index; i++)
        printf("%d ", h->data[i]);
    putchar('\n');
}

int main(void)
{
    heap* h = init_heap(100);

    insert(h, 937);
    insert(h, 457);
    insert(h, 15);
    insert(h, 180);
    insert(h, 85);
    insert(h, 358);
    insert(h, 136);
    insert(h, 984);
    insert(h, 569);
    insert(h, 508);
    insert(h, 20);

    print_heap(h);

    int rt = get_min(h);
    printf("%d\n", rt);
    rt = get_min(h);
    printf("%d\n", rt);

    insert(h, 500);
    print_heap(h);

    free_heap(h);
    return 0;
}