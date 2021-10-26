#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

int main(void)
{
    Heap h;
    initHeap(&h, 12);

    enqueue(&h, 88);
    enqueue(&h, 2);
    enqueue(&h, 905);
    enqueue(&h, 972);
    enqueue(&h, 376);
    enqueue(&h, 9);
    enqueue(&h, 649);
    enqueue(&h, 693);
    enqueue(&h, 529);
    enqueue(&h, 784);
    enqueue(&h, 524);

    levelOrder(&h);
    while (h.count > 0)
        printf("%d ", dequeue(&h));
    putchar('\n');
    
    freeAll(&h);
    return 0;
}