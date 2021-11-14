#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

int main(void)
{
    Stack stk;

    init_stack(&stk);
    push(&stk, 520);
    push(&stk, 10);
    push(&stk, 37);
    push(&stk, 100);

    printf("Peeked number in the stack: %d\n", peek(&stk));
    printf("Items: ");
    traverse(&stk);
    putchar('\n');

    pop(&stk);
    pop(&stk);
    pop(&stk);
    pop(&stk);
    pop(&stk); // It should print error message.
    traverse(&stk); // Also.

    puts("Push 1 in the stack.");
    push(&stk, 1);
    printf("Items: ");
    traverse(&stk);

    free_all(&stk);
    return 0;
}

/*
Input: 
No input

Output:
Peeked number in the stack: 100
Items: 100 37 10 520

ERROR: The stack is empty.
ERROR: The stack is empty.
Push 1 in the stack.
Items: 1
*/