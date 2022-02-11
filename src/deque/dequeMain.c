#include <stdio.h>
#include <stdbool.h>
#include "deque.h"

int main(void)
{
    deque dq;

    init_deque(&dq);

    push_front(&dq, 747);
    push_front(&dq, 920);
    push_back(&dq, 464);
    push_back(&dq, 993);
    push_back(&dq, 977);
    traverse(&dq);
    printf("Items: %d\n", get_size(&dq));

    pop_front(&dq);
    pop_back(&dq);
    traverse(&dq);

    pop_back(&dq);
    pop_back(&dq);
    pop_back(&dq);
    pop_back(&dq);
    traverse(&dq);

    free_all(&dq);
    return 0;
}

/*
Input: 
No input

Output:
920 747 464 993 977
Items: 5
747 464 993
ERROR: The deque is empty.
ERROR: The deque is empty.
*/