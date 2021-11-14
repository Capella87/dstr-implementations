#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

int main(void)
{
    Queue q;

    init_queue(&q);
    enqueue(&q, 520);
    enqueue(&q, 10);
    enqueue(&q, 37);
    enqueue(&q, 100);

    printf("Front number in the queue: %d\n", front(&q));
    printf("Back number in the queue: %d\n", back(&q));
    printf("Items: ");
    traverse(&q);
    putchar('\n');

    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q); // It should print error message.
    traverse(&q); // Also.

    puts("Enqueue 1 in the queue.");
    enqueue(&q, 1);
    printf("Items: ");
    traverse(&q);

    free_all(&q);
    return 0;
}

/*
Input: 
No input

Output:
Front number in the queue: 520
Back number in the queue: 100
Items: 520 10 37 100

ERROR: The queue is empty.
ERROR: The queue is empty.
Enqueue 1 in the stack.
Items: 1
*/