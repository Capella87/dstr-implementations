#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include "stack.h"

// Implement stack based on doubly-linked list. There is no limitation on maximum size in theoretically.

Node* get_node(const Data d) // Make a new node for stack. Returns NULL if there's error in an allocation process.
{
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;

    n->prev = n->next = NULL;
    n->d = d;
    return n;
}

bool init_stack(Stack* stk) // Initialize stack.
{
    stk->head = get_node(-1);
    stk->trailer = get_node(-1);
    if (!stk->head || !stk->trailer) return false;

    stk->head->next = stk->trailer;
    stk->head->prev = stk->trailer->next = NULL;
    stk->trailer->prev = stk->head;
    stk->size = 0;
    return true;
}

bool push(Stack* stk, const Data d) // Push element in the stack.
{
    Node* t = get_node(d);
    if (!t) return false;

    t->next = stk->head->next;
    t->prev = stk->head;
    stk->head->next = t->next->prev = t;
    stk->size++;
    return true;
}

Data pop(Stack* stk) // Pop element from the stack. Returns removed element's data.
{
    if (is_empty(stk))
    {
        fprintf(stderr, "ERROR: The targeted stack is empty.\n");
        goto err_exit;
    }
    Node* temp = stk->head->next;
    Data rt = temp->d;
    stk->head->next = temp->next;
    temp->next->prev = stk->head;
    stk->size--;
    free(temp);
    return rt;

err_exit:
    return -1;
}
Data peek(const Stack* stk) // Returns front element's data. Returns -1 when there is no item in stack.
{
    if (is_empty(stk))
    {
        fprintf(stderr, "ERROR: The targeted stack is empty.\n");
        goto err_exit;
    }

    return stk->head->next->d;
err_exit:
    return -1;
}

bool traverse(Stack* stk) // Print all elements in the stack. Returns false when the stack is empty.
{
    if (is_empty(stk))
    {
        fprintf(stderr, "ERROR: There's no item in the stack.\n");
        return false;
    }

    Node* cur = stk->head->next;
    while (cur != stk->trailer)
    {
        printf("%d ", cur->d);
        cur = cur->next;
    }
    putchar('\n');
    return true;
}

int get_size(const Stack* stk) // Returns current size of the stack.
{
    return stk->size;
}

bool is_empty(const Stack* stk) // Returns true if the stack is vacant.
{
    return !stk->size ? true : false;
}

bool free_all(Stack* stk) // Remove all elements and deallocate memory.
{
    while (!is_empty(stk)) pop(stk);
    free(stk->head);
    free(stk->trailer);
    return true;
}