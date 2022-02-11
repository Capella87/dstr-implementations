#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "deque.h"

node* get_node(const data d)
{
    node* n = (node*)malloc(sizeof(node));
    if (!n) return NULL;
    
    n->next = n->prev = NULL;
    n->d = d;
    return n;
}

bool init_deque(deque* dq)
{
    dq->head = get_node(-1);
    dq->trailer = get_node(-1);
    if (!dq->head || !dq->trailer)
    {
        fprintf(stderr, "ERROR: Could not allocate memory.\n");
        goto err_exit;
    }

    dq->head->next = dq->trailer;
    dq->head->prev = dq->trailer->next = NULL;
    dq->trailer->prev = dq->head;
    dq->size = 0;

    return true;
err_exit:
    return false;
}

data front(deque* dq)
{
    if (is_empty(dq))
    {
        fprintf(stderr, "ERROR: The %s is empty.\n", OBJ);
        goto err_exit;
    }

    return dq->head->next->d;
err_exit:
    return -1;
}

data back(deque* dq)
{
    if (is_empty(dq))
    {
        fprintf(stderr, "ERROR: The %s is empty.\n", OBJ);
        goto err_exit;
    }

    return dq->trailer->prev->d;
err_exit:
    return -1;
}

bool push_front(deque* dq, const data d)
{
    node* t = get_node(d);
    if (!t)
    {
        fprintf(stderr, "ERROR: Could not allocate memory\n");
        goto err_exit;
    }

    t->next = dq->head->next;
    t->prev = dq->head;
    dq->head->next->prev = t;
    dq->head->next = t;
    dq->size++;

    return true;
err_exit:
    return false;
}

bool push_back(deque* dq, const data d)
{
    node* t = get_node(d);
    if (!t)
    {
        fprintf(stderr, "ERROR: Could not allocate memory\n");
        goto err_exit;
    }

    t->next = dq->trailer;
    t->prev = dq->trailer->prev;
    dq->trailer->prev->next = t;
    dq->trailer->prev = t;
    dq->size++;

    return true;
err_exit:
    return false;
}

data pop_front(deque* dq)
{
    if (is_empty(dq))
    {
        fprintf(stderr, "ERROR: The %s is empty.\n", OBJ);
        return -1;
    }
    node* temp = dq->head->next;
    data rt = temp->d;
    dq->head->next = temp->next;
    temp->next->prev = dq->head;
    dq->size--;
    free(temp);

    return rt;
}

data pop_back(deque* dq)
{
    if (is_empty(dq))
    {
        fprintf(stderr, "ERROR: The %s is empty.\n", OBJ);
        return -1;
    }
    node* temp = dq->trailer->prev;
    data rt = temp->d;
    temp->prev->next = dq->trailer;
    dq->trailer->prev = temp->prev;
    dq->size--;
    free(temp);

    return rt;
}

bool traverse(deque* dq)
{
    if (is_empty(dq))
    {
        fprintf(stderr, "ERROR: The %s is empty.\n", OBJ);
        return false;
    }

    node* cur = dq->head->next;
    while (cur != dq->trailer)
    {
        printf("%d ", cur->d);
        cur = cur->next;
    }
    putchar('\n');

    return true;
}

int get_size(const deque* dq)
{
    return dq->size;
}

bool is_empty(const deque* dq)
{
    return !dq->size ? true : false;
}

bool free_all(deque* dq)
{
    while (!is_empty(dq)) pop_front(dq);
    free(dq->head);
    free(dq->trailer);

    return true;
}