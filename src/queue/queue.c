#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

Node* get_node(const Data d)
{
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;
    
    n->next = n->prev = NULL;
    n->d = d;
    return n;
}

bool init_queue(Queue* q)
{
    q->head = get_node(-1);
    q->trailer = get_node(-1);
    if (!q->head || !q->trailer)
    {
        fprintf(stderr, "ERROR: Could not allocate memory.\n");
        goto err_exit;
    }

    q->head->next = q->trailer;
    q->head->prev = q->trailer->next = NULL;
    q->trailer->prev = q->head;
    q->size = 0;

    return true;
err_exit:
    return false;
}

bool enqueue(Queue* q, const Data d)
{
    Node* t = get_node(d);
    if (!t)
    {
        fprintf(stderr, "ERROR: Could not allocate memory.\n");
        goto err_exit;
    }

    t->next = q->trailer;
    t->prev = q->trailer->prev;
    q->trailer->prev->next = t;
    q->trailer->prev = t;
    q->size++;

    return true;
err_exit:
    return false;
}

Data front(Queue* q)
{
    if (is_empty(q))
    {
        fprintf(stderr, "ERROR: The %s is empty.\n", OBJ);
        goto err_exit;
    }

    return q->head->next->d;
err_exit:
    return -1;
}

Data back(Queue* q)
{
    if (is_empty(q))
    {
        fprintf(stderr, "ERROR: The %s is empty.\n", OBJ);
        goto err_exit;
    }

    return q->trailer->prev->d;
err_exit:
    return -1;
}

Data dequeue(Queue* q)
{
    if (is_empty(q))
    {
        fprintf(stderr, "ERROR: The %s is empty.\n", OBJ);
        return -1;
    }
    Node* temp = q->head->next;
    Data rt = temp->d;
    q->head->next = temp->next;
    temp->next->prev = q->head;
    q->size--;
    free(temp);

    return rt;
}

bool traverse(Queue* q)
{
    if (is_empty(q))
    {
        fprintf(stderr, "ERROR: The %s is empty.\n", OBJ);
        return false;
    }

    Node* cur = q->head->next;
    while (cur != q->trailer)
    {
        printf("%d ", cur->d);
        cur = cur->next;
    }
    putchar('\n');

    return true;
}

int get_size(const Queue* q)
{
    return q->size;
}

bool is_empty(const Queue* q)
{
    return !q->size ? true : false;
}

bool free_all(Queue* q)
{
    while (!is_empty(q)) dequeue(q);
    free(q->head);
    free(q->trailer);

    return true;
}
